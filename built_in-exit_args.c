#include "shell.h"



/**
 * our_exit_handler - handles exiting the shell with optional exit status
 * @arg: a string argument representing the desired exit status (optional)
 *
 * The function takes an optional argument `arg`:
 *   - If `arg` is NULL (absent), the program exits normally.
 *     - A message "Exiting shell" is printed.
 *     - The program exits with a success code (0).
 *   - If `arg` is not NULL, it's assumed to be a string containing a
 * numeric exit code.
 *     - The string is converted to an integer using `atoi`.
 *     - A message "Exiting shell with status: %d" is printed, where %d is
 * replaced with the converted exit code.
 *     - The program exits with the provided exit code, conveying success
 * or failure information.
 *
 * This allows the shell program to log or communicate its exit status to
 *the operating system and other processes.
 */


void our_exit_handler(char *arg)
{
	if (arg == NULL)
	{
		printf("Exiting shell\n");
		exit(0);
	}
	else
	{
		int status = atoi(arg);

		printf("Exiting shell with status: %d\n", status);
		exit(status);
	}
}

