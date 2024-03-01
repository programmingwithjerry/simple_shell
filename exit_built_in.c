#include "shell.h"


/**
 * execute_exit_command - terminates the shell program
 *
 * Prints an exit message and exits the program successfully.
 *
 * Returns:
 *   - Nothing (void function).
 */

void execute_exit_command(void)
{
	isjerry_print("Exiting the shell...\n");
	exit(EXIT_SUCCESS);
}

