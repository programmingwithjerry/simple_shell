#include "shell.h"

/**
 * _erratoi - Converts a string to an integer with error handling.
 * @s: Pointer to the string to be converted.
 * Return: Returns the converted integer on success, -1 on failure.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	/* Skip leading '+' character if present */
	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	/* Use a while loop to iterate through the characters of the string */
	while (s[i] != '\0')
	{
		/* Check if the character is a digit */
		if (s[i] >= '0' && s[i] <= '9')
		{
			/* Convert the character to an integer and update the result */
			result *= 10;
			result += (s[i] - '0');

			/* Check for overflow, return -1 if result exceeds INT_MAX */
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			/* Return -1 if a non-digit character is encountered */
			return (-1);
		}

		/* Move to the next character in the string */
		i++;
	}

	/* Return the converted integer on success */
	return (result);
}


/**
 * print_error - Prints an error message to the standard error stream.
 *
 * @info: Pointer to the info_t struct containing shell information.
 * @estr: Pointer to the error message string to be printed.
 */
void print_error(info_t *info, char *estr)
{
	/* Print the program name followed by a colon and a space */
	_eputs(info->fname);
	_eputs(": ");
	/* Print the line count followed by a colon and a space */
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");

	/* Print the command name followed by a colon and a space */
	_eputs(info->argv[0]);
	_eputs(": ");

	/* Print the provided error string */
	_eputs(estr);
}



/**
 * print_d - Prints an integer to the specified file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to which the integer is printed.
 * Return: Returns the number of characters printed.
 */
int print_d(int input, int fd)
{
	/* Function pointer for putchar, default to _putchar */
	int (*__putchar)(char) = _putchar;
	int count = 0;
	unsigned int _abs_, current;

	/* Set __putchar to _eputchar if printing to STDERR_FILENO */
	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	/* Use a while loop to print each digit of the integer */
	while (current > 0)
	{
		int divisor = 1;
		/* Calculate the divisor for the current digit */
		for (int i = 1; i < current; i *= 10)
		{
			divisor *= 10;
		}
		/* Print the current digit and update the count */
		__putchar('0' + current / divisor);
		count++;
		current %= divisor;
	}
	/* If the input is 0, print '0' and update the count */
	if (_abs_ == 0)
	{
		__putchar('0');
		count++;
	}
	return (count);
}



/**
 * convert_number - Converts a long integer to a string
 *representation in a given base.
 * @num: The long integer to be converted.
 * @base: The base for conversion (e.g., 10 for decimal).
 * @flags: Flags for additional formatting (CONVERT_UNSIGNED,
 * CONVERT_LOWERCASE, etc.).
 * Return: Returns a pointer to the converted string.
 */
char *convert_number(long int num, int base, int flags)
{
	/* Static array to store the character set for conversion */
	static char *array;
	/* Buffer to store the converted string */
	static char buffer[50];
	/* Character to store the sign ('-' for negative numbers) */
	char sign = 0;
	/* Pointer to the buffer for building the string */
	char *ptr;
	/* Use an unsigned long variable for conversion if the number is negative */
	unsigned long n = num;

	/* Adjust sign and convert to positive value if necessary */
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	/* Set the character set based on the flags (lowercase or uppercase) */
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	/* Initialize the pointer to the end of the buffer and add null terminator */
	ptr = &buffer[49];
	*ptr = '\0';
	/* Use a do-while loop for conversion */
	do	{
	/**
	* Decrement the pointer and store the corresponding
	 * character in the buffer
	*/
	*--ptr = array[n % base];
	/* Update n for the next digit */
	n /= base;
	} while (n != 0);
	/* Add the sign character if the number was negative */
	if (sign)
		*--ptr = sign;
	/* Return a pointer to the converted string */
	return (ptr);
}


/**
 * remove_comments - Removes comments from a string by replacing '#'
 * and everything after it with '\0'.
 * @buf: Pointer to the string to be processed.
 */
void remove_comments(char *buf)
{
	int i;

	/* Iterate through the characters of the string */
	for (i = 0; buf[i] != '\0'; i++)
	{
		/**
		* Check for '#' and ensure it is either the first character
		*or preceded by a space
		*/
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			/* Replace '#' and everything after it with null terminator */
			buf[i] = '\0';
			break;  /*Exit the loop after the first comment is found*/
		}
	}
}


