#include "shell.h"

/**
 * our_cd_builtin - changes the current working directory
 * @directory: the path to the new directory or a special character
 * This function implements the built-in `cd` command, which allows
 *users to change the current working directory. It handles the
 *following cases:
 *   - If no argument is provided or the argument is "~" (tilde),
 *the user's home directory (obtained from the `HOME` environment
 *variable) is used.
 *   - If the argument is "-" (hyphen), the function changes to the
 *previously accessed directory (obtained from the `PWD` environment
 *variable).
 *   - Otherwise, the provided argument is assumed to be a path to
 *the new directory.
 * The function performs the following actions:
 *   - Attempts to change the directory using `chdir`.
 * - If successful, retrieves the new current working directory
 * using `getcwd` and stores it in the `cwd` buffer.
 * - Updates the `PWD` environment variable using `setenv` to reflect
 * the new working directory.
 *- Returns 0 on success, indicating successful directory
 *  change and environment variable update.
 *  - Returns -1 on failure, indicating an error during the process,
 *   and prints an error message using `perror`.
 * Return:- 0 on success (directory changed and environment variable updated).
 *   - -1 on failure (error during directory change or
 *environment variable update).
 */

int our_cd_builtin(char *directory)
{
	char *home_dir = getenv("HOME");
	char *prev_dir = getenv("PWD");
	char cwd[1024];

	if (directory == NULL || strcmp(directory, "~") == 0)
	{
		directory = home_dir;
	} else if (strcmp(directory, "-") == 0)
		directory = prev_dir;


	if (chdir(directory) != 0)
	{
		perror("Error: Unable to change directory");
		return (-1);
	}

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Error: Unable to get current directory");
		return (-1);
	}

	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("Error: Unable to update PWD environment variable");
		return (-1);
	}

	return (0);
}

