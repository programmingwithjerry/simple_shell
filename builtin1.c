#include "shell.h"

/**
 * _myhistory - Shows the command history list with each command displayed
 * on a separate line, accompanied by line numbers starting from 0.
 * @info: Struct containing potential arguments. Used to maintain
 *  constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * unset_alias - sets alias to string
 * @info: parameter structure
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	/* Find the position of '=' in the alias string */
	p = _strchr(str, '=');
	if (!p)
		return (1);
	/* Save the character at position '=' and replace it with null */
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	/* Restore the character at position '=' */
	*p = c;

	/* Return the result of delete_node_at_index */
	return (ret);
}


/**
 * set_alias - sets alias to string
 * @info: parameter structure
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	/* If '=' is not found, return failure */
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	/* Unset the alias to avoid duplicates and add the new alias to the list */
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}



/**
 * print_alias - prints an alias string
 * @node: alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	/* Check if the node is not NULL */
	if (node)
	{
		p = _strchr(node->str, '=');
		/* Print characters up to and including '=' */
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Struct containing potential args. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		/* Display all aliases */
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	/* Loop through arguments and handle aliases */
	i = 1;
	while (info->argv[i])
	{
		p = _strchr(info->argv[i], '=');
		/* Set alias if argument contains '=' */
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		/* Move to the next argument */
		i++;
	}

	return (0);
}
