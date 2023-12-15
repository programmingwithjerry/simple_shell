#include "shell.h"

/**
 * input_buf - Reads input into a buffer, processes it,
 * and buffers chained commands.
 * @info: Pointer to the parameter struct (info_t)
 * containing relevant information.
 * @buf: Address of the buffer pointer where the input will be stored.
 * @len: Address of the length variable associated with the buffer.
 * This function is designed to handle dynamic memory
 *allocation for the input buffer,
 * removing trailing newlines, eliminating comments,
 *building a history list, and checking
 * for a command chain (though the condition for checking
 * is currently commented out).
 * Return: The number of bytes read into the buffer.
 *If an error occurs or the end of the file
 * is reached, a value less than 0 is returned.
 * The function updates the len variable and
 * the cmd_buf field in the info_t structure if a line is successfully read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/* Free the existing buffer before reading a new line */
		free(*buf);
		*buf = NULL;
		/* Set a signal handler for SIGINT (Interrupt signal) */
		signal(SIGINT, sigintHandler);

		/* Use getline or a custom _getline function*/
#if USE_GETLINE
	r = getline(buf, &len_p, stdin);
#else
	r = _getline(info, buf, &len_p);
#endif
		/* If a line is successfully read */
		if (r > 0)
		{
			/* Remove trailing newline character, if present */
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			/* Build a history list with the input line, increment history count */
			build_history_list(info, *buf, info->histcount++);
			/* Update the length and command buffer in the info structure */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}

	return (r);
}



/**
 * get_input - Gets input from the user, handles command chaining.
 * @info: Pointer to the parameter struct (info_t) containing
 * relevant information.
 * This function manages the input buffer,
 * processing command chaining and updating
 * information in the info_t structure accordingly.
 * It handles the static buffer for
 * command chaining and passes back the pointer to the
 * current command position.
 * Return: The length of the current command or the length of
 * the buffer from _getline().
 * If an error occurs or the end of the file is reached,
 * a value less than 0 is returned.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	/* Flush the buffer */
	_putchar(BUF_FLUSH);
	/* Read input into the buffer and handle EOF */
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	/* Check if there are commands left in the chain buffer */
	if (len)
	{
		j = i; /* Initialize new iterator to the current buf position */
		p = buf + i; /* Get pointer for return */
		/* Check for command chain and update iterator */
		check_chain(info, buf, &j, i, len);
		/* Iterate to semicolon or end of buffer */
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}
		i = j + 1; /* Increment past nulled ';'' */
		/* Reached the end of the buffer? Reset position and length */
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /* Pass back pointer to the current command position */
		return (_strlen(p)); /* Return length of the current command */
	}
	*buf_p = buf;
	return (r);
}



/**
 * read_buf - Reads data into a buffer from a file descriptor.
 * @info: Pointer to the parameter struct (info_t)
 * containing relevant information.
 * @buf: Buffer to store the read data.
 * @i: Pointer to a size_t variable representing the
 * current position in the buffer.
 * This function reads data into the provided buffer from
 * the specified file descriptor
 * in the info_t structure. It updates the position
 * indicator (i) based on the amount
 * of data read. If the position indicator is already non-zero,
 * indicating that there is
 * unread data in the buffer, the function returns 0 without performing
 * a read operation.
 * Return: The number of bytes read into the buffer.
 * If an error occurs or the end of
 * the file is reached, a value less than 0 is returned,
 * If the position indicator is
 * non-zero, indicating unread data in the buffer, the function
 * returns 0 without reading.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	/* Check if there is unread data in the buffer */
	if (*i)
		return (0);

	/* Read data into the buffer from the specified file descriptor */
	r = read(info->readfd, buf, READ_BUF_SIZE);

	/* Update the position indicator based on the amount of data read */
	if (r >= 0)
		*i = r;

	return (r);
}



/**
 * _getline - Reads a line from the specified file descriptor into a buffer.
 * @info: Pointer to the parameter struct (info_t) containing
 *	relevant information.
 * @ptr: Pointer to a pointer to the buffer where the line will be stored.
 * @length: Pointer to a size_t variable representing
 *	the length of the buffer.
 * This function reads a line from the specified file descriptor
 *	using a buffer and
 * dynamically reallocates memory to accommodate the growing line.
 *	It updates the
 * buffer pointer, buffer length, and returns the length of the read line.
 * Return: The length of the read line. If an error occurs or
 *	the end of the file is
 * reached, a value less than 0 is returned. If memory allocation fails,
 *	the function
 * returns -1. The buffer pointer and length are updated with the
 *	newly read line.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	/* Retrieve current length if provided */
	if (p && length)
		s = *length;
	/* Reset buffer position if it has reached the end */
	if (i == len)
		i = len = 0;
	/* Read data into the buffer */
	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	/* Find the position of the newline character or set k to the buffer length */
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	/* Reallocate memory for the buffer */
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	/* Concatenate the newly read data to the buffer */
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	/* Update position, buffer pointer, and length */
	s += k - i;
	i = k;
	p = new_p;
	/* Update length if provided */
	if (length)
		*length = s;
	/* Update buffer pointer */
	*ptr = p;
	return (s);
}


/**
 * sigintHandler - Signal handler for the SIGINT (Interrupt signal).
 * @sig_num: The signal number (unused, specified by __attribute__((unused))).
 * This function is invoked when the SIGINT signal is received,
 *	typically triggered by
 * pressing Ctrl+C in the terminal. It prints a newline character,
 *	the prompt "$ ", and
 * flushes the output buffer.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	/* Print a newline character */
	_puts("\n");
	/* Print the prompt "$ " */
	_puts("$ ");
	/* Flush the output buffer */
	_putchar(BUF_FLUSH);
}

