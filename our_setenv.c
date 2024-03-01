#include "shell.h"


/**
   * isjerry_setenv_builtin - sets an environment variable
   * @variable: the name of the environment variable to be set
   * @value: the value to be assigned to the environment variable
   * This function attempts to set an environment variable using the
   *`setenv` function from the standard C library. It performs the
   *following checks and actions:
   * - Checks for invalid arguments (NULL pointers).
   * - Calls `setenv` to set the environment variable with the provided
   *`variable` name and `value`. The third argument (`1`) to `setenv`
   *indicates to overwrite existing variables with the same name.
   * - Returns an error code (-1) on failure, indicating either invalid
   *arguments or an error during the setting process using `perror`.
   *- Returns 0 on success, signifying the environment variable
   * was successfully set.
   * Return:
   *   - 0 on success, indicating the environment
   * variable was set successfully.
   *   - -1 on failure, indicating an error occurred (e.g.,
   *invalid arguments, unable to set the variable).
   */


int isjerry_setenv_builtin(const char *variable, const char *value)
{
	if (variable == NULL || value == NULL)
	{
		perror("Error: Invalid arguments");
		return (-1);
	}

	if (setenv(variable, value, 1) != 0)
	{
		perror("Error: Unable to set environment variable");
		return (-1);
	}

	return (0);
}

