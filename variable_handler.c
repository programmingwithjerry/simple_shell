#include "shell.h"

/**
*handle_variables - replaces specific variables in a string
*This function processes a string and replaces specific variable
*references
*with their corresponding values. It handles the following variables:
*$$: Replaced with the current process ID (PID)
*$?: Replaced with a placeholder value (example: "0" for success)
*The function dynamically allocates memory for the output string
 *and returns a pointer
*to the newly created string. If an error occurs during memory
 *allocation, the
*function returns NULL.
*@input: the input string containing variables to be replaced
*Return: a pointer to the processed string, or NULL on error
*/

char *handle_variables(char *input)
{
	char *output = (char *)malloc(strlen(input) * sizeof(char));
	int out_pos = 0;
	int in_pos = 0;

	while (input[in_pos] != '\0')
	{
		/*Check for variable replacement*/
		if (input[in_pos] == '$')
		{
			if (input[in_pos + 1] == '$')
			{
			/*Replace $$ with process ID*/
			char pid[10];

			snprintf(pid, sizeof(pid), "%d", getpid());
			strcat(output, pid);
			out_pos += strlen(pid);
			in_pos += 2;
			}
			else if (input[in_pos + 1] == '?')
			{
			strcat(output, "0");
			out_pos++;
			in_pos += 2;
			}
			else
			{
			output[out_pos++] = input[in_pos++];
			}
		}
		else
		{
			output[out_pos++] = input[in_pos++];
		}
	}
	output[out_pos] = '\0';
	return (output);
}
