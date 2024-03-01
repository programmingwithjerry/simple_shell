#include "shell.h"

/**
 * isjerry_or_handler - executes multiple commands sequentially until one succeeds
 * @input: a string containing commands separated by "||" (OR operator)
 * This function takes a string containing multiple commands separated by the
 * logical OR operator ("||"). It executes each command sequentially
 *until one of
 * the commands exits with a success code (exit code 0). If all commands fail,
 * the function does nothing and simply returns.
 * Here's a breakdown of the function's logic:
 */


void isjerry_or_handler(char *input)
{
	char *command = strtok(input, "||");

	while (command != NULL)
 	{
		execute_command(command);
		command = strtok(NULL, "||");
	}
}

