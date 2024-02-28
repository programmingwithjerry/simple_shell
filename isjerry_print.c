#include "shell.h"


/**
 * isjerry_print - formatted printing function
 * @format: format string similar to printf
 * @...: variable number of arguments
 * This function is similar to `printf` but offers more control over memory
 * allocation and error handling. It takes a format string
 * and a variable number
 * of arguments, similar to `printf`. It formats the message according to the
 * format string and the arguments, then prints it to an unspecified output
 * stream (likely standard output).
 * Return: Number of bytes written on success, or -1 on error.
 */

int isjerry_print(const char *format, ...)
{
	va_list args, copy;
	int len;
	char *buf;
	/*buf = malloc(len + 1);*/

	if (!format || format[strlen(format)] != '\0')
	{
		return (-1);
	}
	va_start(args, format);
	va_copy(copy, args);

	len = vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	if (len < 0)
	{
		perror("vsnprintf");
		return (-1);
	}
	buf = malloc(len + 1);
	if (!buf)
	{
		perror("malloc");
		return (-1);
	}

	va_start(args, format);
	vsnprintf(buf, len + 1, format, args);
	va_end(args);

	if (write(STDOUT_FILENO, buf, len) == -1)
	{
		perror("write");
		free(buf);
		return (-1);
	}
	free(buf);
	return (0);
}





