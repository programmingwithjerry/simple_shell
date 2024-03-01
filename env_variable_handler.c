#include "shell.h"


/**
 * replace_variables - replaces variables in a command string with their values
 * @command: a pointer to the command string to be modified
 *
 * This function modifies a given command string by replacing variables with
 * their corresponding values. It handles three types of variables:
 *
 * 1. **Special Variables:**
 *    - `$?`: Replaced with the exit status of the most recently
 * executed command.
 *    - `$$`: Replaced with the process ID of the current shell.
 *
 * 2. **Environment Variables:**
 *    - Any variable starting with `$` followed by a name
 * (e.g., `$HOME`, `$PATH`)
 *      is replaced with its value from the environment.
 *
 * 3. **Literal `$`:**
 *    - If a `$` is not followed by a special variable or environment variable
 *      pattern, it's kept as a literal `$` in the command string.
 *
 * The function directly modifies the input command string,
 * ensuring the changes
 * are reflected in the original variable. This function is crucial for:
 *
 * - **Dynamic Command Construction:** Customizing commands based on variables.
 * - **Accessing Environment Information:** Utilizing environment variables
 *   for task-specific actions.
 * - **Incorporating Shell State:** Executing actions based on recent command
 *   outcomes (using `$?`) or the current process ID (using `$$`).
 */

void replace_variables(char *command)
{
	char *ptr = command, *p = command, *env_var;
	long pid;
	int len, status;

	while (*ptr)
	{
		if (*ptr == '$')
		{
			ptr++;
			if (*ptr == '?')
			{
				status = WEXITSTATUS(system(NULL));
				len = snprintf(p, MAX_COMMAND_LENGTH - (p - command), "%d", status);
				p += len;
			}
			else if (*ptr == '$')
				{
				pid = getpid();
				len = snprintf(p, MAX_COMMAND_LENGTH - (p - command), "%ld", pid);
				p += len;
			}
			else
			{
				env_var = getenv(ptr);
				if (env_var)
				{
					while (*env_var)
						*p++ = *env_var++;
					while (*ptr && !strchr(" \t\n", *ptr))
						ptr++;
				}
			}
			ptr++;
		} else
		{
			*p++ = *ptr++;
		}
	}
	*p = '\0'; /*Null terminate the buffer*/
}
