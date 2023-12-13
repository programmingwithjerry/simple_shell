#include "shell.h"ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * input_buf - Read input from stdin into a buffer.
 *
 * @info: Pointer to the info_t structure containing shell information.
 * @buf: Pointer to a buffer to store the input.
 * @len: Pointer to the length of the buffer.
 *
 * This function reads input from stdin into the provided buffer. If the buffer
 * is empty or the end of the buffer is reached, it fills the buffer with a new
 * line of input from stdin. The function removes the trailing newline character
 * and updates the 'linecount_flag' and 'histcount' accordingly. If a command
 * chain is detected (presence of ';'), it sets the 'cmd_buf' pointer to 'buf'.
 *
 * Return: The number of characters read on success, or 0 on failure or EOF.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    /* Check if the buffer is empty */
    if (!*len)
    {
        /* Free the existing buffer */
        free(*buf);
        *buf = NULL;

        /* Set up a signal handler for SIGINT */
        signal(SIGINT, sigintHandler);

        /* Use getline or custom function _getline to read input from stdin */
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif

        /* Check if characters were read successfully */
        if (r > 0)
        {
            /* Remove trailing newline if present */
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }

            /* Set flags and update history list for the input */
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            /* Check if a command chain is present (';') */
            if (_strchr(*buf, ';'))
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }

    /* Return the number of characters read */
    return r;
}

/**
 * get_input - Get input from the user.
 *
 * @info: Pointer to the info_t structure containing shell information.
 *
 * This function retrieves input from the user, either from the command chain
 * buffer or by calling the input_buf function. It updates the 'arg' pointer
 * in the info_t structure to point to the current command in the buffer or the
 * latest input from input_buf. It also returns the length of the input.
 *
 * Return: The length of the input on success, -1 on EOF, or 0 on failure.
 */
ssize_t get_input(info_t *info)
{
    static char *buf; /* the ';' command chain buffer */
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);

    /* Check for EOF */
    if (r == -1)
        return -1;

    /* Check if there are commands left in the chain buffer */
    if (len)
    {
        j = i;       /* Initialize new iterator to the current buf position */
        p = buf + i; /* Get pointer for return */

        check_chain(info, buf, &j, i, len);

        /* Iterate to semicolon or end */
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

        *buf_p = p;        /* Pass back pointer to the current command position */
        return _strlen(p); /* Return the length of the current command */
    }

    *buf_p = buf; /* Not a chain, pass back buffer from _getline() */
    return r;     /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Read data into the buffer.
 *
 * @info: Pointer to the info_t structure containing shell information.
 * @buf: Buffer to read data into.
 * @i: Pointer to the current position in the buffer.
 *
 * This function reads data into the buffer from the file descriptor 'readfd'
 * in the info_t structure. It updates the 'i' pointer with the number of
 * bytes read. If there is data already present in the buffer, it returns 0.
 *
 * Return: The number of bytes read on success, or -1 on failure.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    /* If there is already data in the buffer, return 0 */
    if (*i)
        return 0;

    /* Read data into the buffer from the file descriptor 'readfd' */
    r = read(info->readfd, buf, READ_BUF_SIZE);

    /* Update the 'i' pointer with the number of bytes read */
    if (r >= 0)
        *i = r;

    return r; /* Return the number of bytes read on success, or -1 on failure */
}

/**
 * _getline - Read a line from the input into a buffer.
 *
 * @info: Pointer to the info_t structure containing shell information.
 * @ptr: Pointer to the buffer to store the read line.
 * @length: Pointer to the length of the buffer.
 *
 * This function reads a line from the input file descriptor 'info->readfd'
 * into the buffer 'ptr'. It updates the 'length' pointer with the length of
 * the buffer. The buffer is reallocated if necessary. It returns the number
 * of bytes read on success, -1 on failure, or 0 at the end of the input.
 *
 * Return: The number of bytes read on success, -1 on failure, or 0 at EOF.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;

    if (p && length)
        s = *length;

    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);

    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;

    new_p = _realloc(p, s, s ? s + k : k + 1);

    if (!new_p) /* MALLOC FAILURE! */
        return p ? (free(p), -1) : -1;

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;

    *ptr = p;
    return s;
}

/**
 * sigintHandler - Signal handler for SIGINT (Ctrl+C).
 *
 * @sig_num: The signal number.
 *
 * This function is the handler for the SIGINT signal (Ctrl+C). It prints a
 * newline character, the shell prompt, and flushes the output buffer.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");         /* Print newline character */
    _puts("$ ");         /* Print shell prompt */
    _putchar(BUF_FLUSH); /* Flush the output buffer */
}