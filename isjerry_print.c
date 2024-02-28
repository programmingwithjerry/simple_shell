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
	va_list args;
	va_list args_copy; /*Create a copy of the va_list*/
	int length;
	char *message;
	ssize_t bytes_written;

	if (format == NULL || format[strlen(format)] != '\0')
	{
		return (-1); /* Indicate error: null-termination missing */
	}
	va_start(args, format);
	va_copy(args_copy, args);
	length = vsnprintf(NULL, 0, format, args_copy);
	if (length < 0)
	{
		perror("vsnprintf"); /* Print error message if vsnprintf fails */
		va_end(args); /* Clean up the original va_list*/
		va_end(args_copy); /* Clean up the copied va_list*/
		return (-1); /* Indicate error */
	}
	message = (char *)malloc(length + 1); /* +1 for the null terminator */
	if (message == NULL)
	{
		perror("malloc"); /* Print error message if malloc fails */
		va_end(args); /* Clean up the original va_list*/
		va_end(args_copy); /* Clean up the copied va_list*/
		return (-1); /* Indicate error */
	}
	vsnprintf(message, length + 1, format, args);
	bytes_written = write(STDOUT_FILENO, message, strlen(message));
	if (bytes_written == -1)
	{
		perror("write"); /* Print error message if write fails */
		free(message); /* Free the allocated memory */
		va_end(args); /* Clean up the original va_list*/
		va_end(args_copy); /* Clean up the copied va_list*/
		return (-1); /* Indicate error */
	}
	free(message);
	va_end(args); /* Clean up the original va_list*/
	va_end(args_copy); /* Clean up the copied va_list*/
	return (0); /* Indicate success */
}




