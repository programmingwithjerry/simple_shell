#include "shell.h"


/**
 * our_get_command - reads a command from standard input
 * @command: address of character array to store the command
 * @size: maximum size of the command string (including null terminator)
 *
 * Reads a command from standard input and stores it in the provided
 * character array. Handles end-of-file (EOF) and potential read errors.
 * Removes any trailing newline character from the command string.
 *
 * Return:
 *   - Number of bytes read on success.
 *   - 0 on end-of-file (EOF).
 *   - -1 on error.
 */



void our_get_command(char *command, size_t size)
{
	/*Allocate memory for the line buffer*/
	ssize_t nread;
	char *buffer = NULL;
	size_t bufsize = 0;

	/*Read the line using getline*/
	nread = getline(&buffer, &bufsize, stdin);

	/*Check for errors or EOF*/
	if (nread == -1)
	{
		if (feof(stdin))
		{
			isjerry_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			isjerry_print("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}

	/*Remove the newline character (if present)*/
	if (nread > 0 && buffer[nread - 1] == '\n')
	{
		buffer[nread - 1] = '\0';
	}

	/* Copy the command (up to size - 1 characters)*/
	strncpy(command, buffer, size - 1);
	command[size - 1] = '\0'; /*Ensure null termination*/

	/*Free the allocated buffer*/
	free(buffer);
}






/**
 * get_command - reads a command line from standard input
 * @command: a pointer to a character array where the read
 *command will be stored
 * @size: the maximum size of the command string (including
 *the null terminator)
 * This function reads a line of input from the standard input
 *(usually the keyboard)
 * and stores it in the provided character array (`command`).
 *It ensures the command
 * doesn't exceed the specified size limit (`size`).
 */

/**
*void get_command(char *command, size_t size)
*{
*	if (fgets(command, size, stdin) == NULL)
*	{
*		if (feof(stdin))
*		{
*			isjerry_print("\n");
*			exit(EXIT_SUCCESS);
*		}
*		else
*		{
*			isjerry_print("Error while reading input.\n");
*			exit(EXIT_FAILURE);
*
*		}
*	}
*	command[strcspn(command, "\n")] = '\0'; remove new line
*}
*/
