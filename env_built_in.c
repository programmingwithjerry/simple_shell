#include "shell.h"


void print_env_built_in()
{
	extern char **environ; /*Access the global variable environ*/

	/*Declare the variable outside the loop*/
	char **env = environ;

	/*Iterate through the environment variables*/
	while (*env != NULL) {
		printf("%s\n", *env);
		env++;
	}
}

