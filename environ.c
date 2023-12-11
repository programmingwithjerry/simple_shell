#include "shell.h"

/**
 * _myenv - Displays the current environment variables.
 * @info: Pointer to the info_t struct containing shell information.
 * Return: Always returns 0.
 */
int _myenv(info_t *info)
{
	/* Print the list of environment variables */
	print_list_str(info->env);

	/* Return 0 to indicate success */
	return (0);
}



/**
 * _getenv - Retrieves the value of an environment variable.
 *
 * @info: Pointer to the info_t struct containing shell information.
 * @name: Name of the environment variable to retrieve.
 *
 * Return: Returns a pointer to the value of the environment variable
 * if found, otherwise returns NULL.
 */
char *_getenv(info_t *info, const char *name)
{
	/* Start from the beginning of the environment list */
	list_t *node = info->env;
	char *p;

	/* Traverse the environment list */
	while (node)
	{
		/* Check if the environment variable starts with the specified name */
		p = starts_with(node->str, name);

		/* If a match is found and the value is not empty, return the value */
		if (p && *p)
			return (p);

		/* Move to the next node in the environment list */
		node = node->next;
	}

	/* Return NULL if the environment variable is not found */
	return (NULL);
}


/**
 * _mysetenv - Sets an environment variable.
 *
 * @info: Pointer to the info_t struct containing shell information.
 *
 * Return: Returns 0 on success, 1 on failure.
 */
int _mysetenv(info_t *info)
{
	/*
	* Check if the correct number of arguments is provided.
	* If not, print an error message and return 1 to signify failure.
	*/
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	/*
	* Set the environment variable using the provided arguments.
	* If successful, return 0 to signify success.
	*/
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	/* Return 1 to signify failure (default case). */
	return (1);
}




/**
 * _myunsetenv - Unsets environment variables.
 * @info: Pointer to the info_t struct containing shell information.
 *
 * Return: Returns 0 on success, 1 on failure.
 */
int _myunsetenv(info_t *info)
{
	int i = 1;

	/* Check for insufficient arguments */
	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	/* Use a while loop to unset environment variables */
	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}

	/* Return 0 to indicate success */
	return (0);
}






/**
 * populate_env_list - Populates the environment list in the info structure.
 * @info: Pointer to the info_t struct containing shell information.
 * Return: Always returns 0.
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i = 0;

	/* Populate the environment list using a while loop */
	while (environ[i])
	{
		add_node_end(&node, environ[i], 0);
		i++;
	}

	/* Update the env pointer in the info structure */
	info->env = node;

	/* Return 0 to indicate success */
	return (0);
}

