#include "shell.h"

/**
 * my_semicolon_handler - executes multiple commands sequentially
 * @input: a string containing commands separated by semicolons (;)
 *
 * This function takes a string containing multiple commands
 *separated by semicolons (;).
 * It executes each command sequentially, regardless of the success
 *or failure of the
 * previous commands.
 */

void isjerry_semicolon_handler(char *input)
{
	char *command = strtok(input, ";");

	while (command != NULL)
	{
		execute_command(command);
		command = strtok(NULL, ";");
	}
}
