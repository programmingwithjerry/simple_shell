#include "shell.h"



/**
 * my_ampersound_handler - executes commands separated by "&&" (AND operator)
 * @input: string containing commands separated by "&&"
 * This function takes a string containing one or more commands separated by
 * the logical AND operator ("&&"). It iterates through each command,
 * executing them sequentially using the `execute_command` function. **Only if**
 * all commands in the sequence exit with a **zero** exit code, the entire
 * chain is considered successful.
 * Returns: Nothing (void function).
 */

void my_ampersound_handler(char *input)
{
	char *command = strtok(input, "&&");
	while (command != NULL)
	{
		execute_command(command);
		command = strtok(NULL, "&&");
	}
}
