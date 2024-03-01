#include "shell.h"


/**
 * our_unsetenv_builtin - removes an environment variable from
 * the environment
 * @variable: the name of the environment variable to be removed
 * This function attempts to remove an environment variable
 * specified by the
 * `variable` argument from the process's environment list.
 * It first checks
 * for invalid arguments and then calls the `unsetenv`
 * function from the standard
 * C library to perform the actual removal.
 * Return: 0 on success, indicating the environment
 *	variable was successfully removed.
 *     -1 on failure, indicating an error occurred (e.g.,
 *	invalid argument,
 *     unable to remove the variable).
 */

int our_unsetenv_builtin(const char *variable)
{
	if (variable == NULL)
	{
		perror("Error: Invalid argument");
		return (-1);
	}

	if (unsetenv(variable) != 0)
	{
		perror("Error: Unable to unset environment variable");
		return (-1);
	}

	return (0);
}

