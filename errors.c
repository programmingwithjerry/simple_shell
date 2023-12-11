#include "shell.h"

/**
 * _eputs - Outputs a string to the standard error stream.
 * @str: Pointer to the string to be printed.
 */
void _eputs(char *str)
{
	int i = 0;

	/* Check if the input string is NULL */
	if (!str)
		return;
	/* Iterate through the characters of the string and print each character */
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}


/**
 * _eputchar - Outputs a character to the standard error stream.
 * @c: The character to be printed.
 * Return: Always returns 1.
 */
int _eputchar(char c)
{
	/* Buffer size for efficient write to standard error */
	static int i;

	/* Buffer to store characters before writing to standard error */
	static char buf[WRITE_BUF_SIZE];

	/* Check if the character is a flush indicator or buffer size is exceeded */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/* Write the buffer to standard error and reset the buffer index */
		write(2, buf, i);
		i = 0;
	}

	/* If the character is not a flush indicator, store it in the buffer */
	if (c != BUF_FLUSH)
		buf[i++] = c;

	/* Always return 1 to indicate success */
	return (1);
}


/**
 * _putfd - Outputs a character to the specified file descriptor.
 * @c: The character to be printed.
 * @fd: The file descriptor to which the character is printed.
 * Return: Always returns 1.
 */
int _putfd(char c, int fd)
{
	/* Buffer size for efficient write to the specified file descriptor */
	static int i;

	/* Buffer to store characters before writing to specified file descriptor */
	static char buf[WRITE_BUF_SIZE];

	/* Check if the character is a flush indicator or buffer size is exceeded */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		/* Write the buffer to specified file descriptor, reset the buffer index */
		write(fd, buf, i);
		i = 0;
	}
	/* If the character is not a flush indicator, store it in the buffer */
	if (c != BUF_FLUSH)
		buf[i++] = c;
	/* Always return 1 to indicate success */
	return (1);
}


/**
 * _putsfd - Outputs a string to the specified file descriptor.
 * @str: Pointer to the string to be printed.
 * @fd: The file descriptor to which the string is printed.
 * Return: Returns the number of characters printed.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	/* Check if the input string is NULL */
	if (!str)
		return (0);
	/*Iterate through the characters of the string, call _putfd for each char */
	for (; *str; str++)
	{
		i += _putfd(*str, fd);
	}

	/* Return the total number of characters printed */
	return (i);
}

