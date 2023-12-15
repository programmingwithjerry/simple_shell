#include "shell.h"

/**
 * get_environ - Get the environment variables as an array of strings.
 * @info: Pointer to the info_t structure containing environment information.
 * This function retrieves the environment variables from the linked list 'env'
 * in the @info structure and returns them as an array of strings. If the 'env'
 * linked list has changed or is not present in the @info structure, it updates
 * the 'environ' array with the current environment variables and sets the
 * 'env_changed' flag to 0.
 * Return: An array of strings containing the environment variables.
 */
char **get_environ(info_t *info)
{
	/* Check if 'environ' is not present or 'env_changed' is set */
	if (!info->environ || info->env_changed)
	{
		/* Update 'environ' with the current environment variables */
		info->environ = list_to_strings(info->env);

		/* Reset the 'env_changed' flag to 0 */
		info->env_changed = 0;
	}

	/* Return the 'environ' array */
	return (info->environ);
}

/**
 * _unsetenv - Unset an environment variable from the linked list.
 * @info: Pointer to the info_t structure containing environment information.
 * @var: Name of the environment variable to unset.
 * This function unsets the environment variable specified by 'var' from the
 * linked list 'env' in the @info structure. It searches for the variable in
 * the linked list and deletes the corresponding node. The 'env_changed' flag
 * is set to indicate a change in the environment variables.
 * Return: 1 if the environment variable was successfully unset, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	/* Check if 'env' or 'var' is NULL */
	if (!node || !var)
		return (0);

	/* Iterate through the 'env' linked list to find and unset the variable */
	while (node)
	{
		/* Check if the current node's string starts with 'var' followed by '=' */
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* Delete the node at the current index and update 'env_changed' */
			info->env_changed = delete_node_at_index(&(info->env), i);
			/* Reset the index to 0 and update the 'node' pointer */
			i = 0;
			node = info->env;
			/* Continue searching for additional occurrences of the variable */
			continue;
		}

		/* Move to the next node in the linked list */
		node = node->next;
		/* Increment the index */
		i++;
	}
	/* Return the 'env_changed' flag */
	return (info->env_changed);
}

/**
 * _setenv - Set or update an environment variable in the linked list.
 * @info: Pointer to the info_t structure containing environment information.
 * @var: Name of the environment variable to set or update.
 * @value: Value to assign to the environment variable.
 * This function sets or updates the environment variable specified by 'var' in
 * the linked list 'env' in the @info structure. It checks if the variable
 * already exists in the list. If found, it updates the value; otherwise, it
 * adds a new node to the end of the linked list. The 'env_changed' flag is set
 * to indicate a change in the environment variables.
 * Return: 0 if the operation is successful, 1 if memory allocation fails.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	/* Check if 'var' or 'value' is NULL */
	if (!var || !value)
		return (0);
	/* Allocate memory for the concatenated string 'var=value' */
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	/* Concatenate 'var', '=', and 'value' to form 'var=value' */
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	/* Initialize the 'node' pointer to the start of the 'env' linked list */
	node = info->env;
	/* Iterate through the 'env' linked list to find and update the variable */
	while (node)
	{
		/* Check if the current node's string starts with 'var' followed by '=' */
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			/* Free the current node's string and update it with 'buf' */
			free(node->str);
			node->str = buf;
			/* Set 'env_changed' to 1 to indicate a change in environment variables */
			info->env_changed = 1;
			free(buf);/* Free 'buf' and return success */
			return (0);
		}
		node = node->next;
	}
	/* Add a new node to the end of the 'env' linked list with string 'buf' */
	add_node_end(&(info->env), buf, 0);
	/* Free 'buf' and set 'env_changed' to 1 to indicate a change */
	free(buf);
	info->env_changed = 1;
	return (0);
}

