#include "shell.h"




/**
 * isjerry_getline - reads a line of input from standard input
 *
 * This function reads a line of input from the standard input
 *(usually the keyboard)
 * and returns a newly allocated character array containing
 * the entire line. The
 * function allocates memory dynamically, so the caller is responsible
 *for freeing
 * the returned memory using `free` when finished.
 *
 * If an error occurs during reading (e.g., reaching EOF or
 *encountering an error),
 * the function returns `NULL` and sets `errno` to indicate the error.
 */

char *isjerry_getline()
{
	static char buffer[BUFFER_SIZE], *cursor = buffer;
	static size_t line_size = 0;
	char *line = NULL, *newline;
	ssize_t read_chars;

	while ((read_chars = read(STDIN_FILENO, buffer + line_size, BUFFER_SIZE - line_size)) > 0)
	{
		line_size += read_chars;
		newline = memchr(cursor, '\n', line_size);
		if (newline)
		{
			line = realloc(line, line_size + 1);
			if (!line)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			memcpy(line + line_size - (newline - cursor), cursor, newline - cursor + 1);
			line[line_size] = '\0';
			cursor = newline + 1;
			line_size -= (newline - cursor);
			return (line);
		}
	}
	if (read_chars == 0)
	{
		if (line_size)
		{
			line = realloc(line, line_size + 1);
			if (!line)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			memcpy(line, cursor, line_size);
			line[line_size] = '\0';
			line_size = 0;
			cursor = buffer;
			return (line);
		}
		else
			return (NULL);
	}
	else
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
}
