#include "shell.h"

/**
 * get_history_file - Get the path of the history file.
 * @info: Pointer to the info_t structure containing environment information.
 * This function constructs and returns the path of the history file based on
 * the user's home directory. It uses the information in the @info structure
 * to retrieve the home directory from the environment variables. The returned
 * string should be freed by the caller when no longer needed.
 * Return: A dynamically allocated string containing the path of
 *      the history file,  or NULL on failure.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	/* Get the user's home directory from the environment variables */
	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	/* Allocate memory for the buffer to hold the history file path */
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	/* Initialize the buffer with an empty string */
	buf[0] = 0;

	/* Copy the user's home directory to the buffer */
	_strcpy(buf, dir);

	/* Concatenate a forward slash to the buffer */
	_strcat(buf, "/");

	/* Concatenate the history file name to the buffer */
	_strcat(buf, HIST_FILE);

	/* Return the dynamically allocated buffer containing the history file path */
	return (buf);
}

/**
 * write_history - Write the command history to a file.
 * @info: Pointer to the info_t structure containing command
 * history information.
 * This function writes the command history stored in the
 * @info structure to a
 * file. It constructs the file path using the get_history_file
 * function and opens
 * the file for writing. The commands are written to the file,
 * each followed by a
 * newline character. The file is closed after writing.
 * The function returns 1 on
 * success and -1 on failure.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	/* Check if the filename is successfully obtained */
	if (!filename)
		return (-1);

	/* Open the history file for writing or create it if it doesn't exist */
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	/* Check if the file is opened successfully */
	if (fd == -1)
		return (-1);

	/* Iterate through the command history and write each command to the file */
	for (node = info->history; node; node = node->next)
	{
		/* Write the command string to the file */
		_putsfd(node->str, fd);
		/* Write a newline character to separate commands */
		_putfd('\n', fd);
	}
	/* Flush the buffer and close the file */
	_putfd(BUF_FLUSH, fd);
	close(fd);

	/* Return 1 to indicate success */
	return (1);
}

/**
 * read_history - Read command history from a file into a linked list.
 * @info: Pointer to the info_t structure containing command
 * history information.
 *
 * This function reads the command history from a file specified by the
 * get_history_file function into a linked list in the @info structure. It
 * opens the history file for reading, reads its content, and builds a linked
 * list of command strings. The linked list is updated in the @info structure,
 * and the function returns the number of history entries read from the file.
 *
 * Return: The number of history entries read from the file, or 0 on failure.
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)/* Check if the filename is successfully obtained */
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st)) /* Get the size of the history file */
		fsize = st.st_size;
	if (fsize < 2)
		return (close(fd), 0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (close(fd), 0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (close(fd), free(buf), 0);
	close(fd);
	/* Iterate through the buffer and build the history list */
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	/* Build the history list for the last line if not already done */
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Build a history list node and add it to
 * the linked list.
 * @info: Pointer to the info_t structure containing command
 * history information.
 * @buf: Pointer to the command string to be added to the history list.
 * @linecount: Line count associated with the command string.
 * This function creates a new history list node with the
 * specified command string
 * (@buf) and line count (@linecount) and adds it to the end
 * of the linked list
 * in the @info structure. If the history list is not empty,
 * it adds the new node
 * to the end of the existing list; otherwise, it creates a
 * new list with the node.
 * Return: Always returns 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	/* Check if the history list is not empty */
	if (info->history)
		node = info->history;

	/* Add a new node with the specified command string to the end of list */
	add_node_end(&node, buf, linecount);

	/* Update the history list in the info structure */
	if (!info->history)
		info->history = node;

	/* Return 0 to indicate success */
	return (0);
}

/**
 * renumber_history - Renumber the history entries in the linked list.
 * @info: Pointer to the info_t structure containing command history
 * information.
 * This function iterates through the linked list of history entries in the
 * @info structure and assigns sequential numbers to each entry
 * starting from 0.
 * It updates the 'num' field of each history list node accordingly and returns
 * the total number of history entries in the list.
 * Return: The total number of history entries in the list.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	/* Iterate through the history list and assign sequential numbers */
	while (node)
	{
		/* Assign the current sequential number to the 'num' field */
		node->num = i++;
		/* Move to the next node in the history list */
		node = node->next;
	}
	/* Update the total number of history entries in the info structure */
	return (info->histcount = i);
}
