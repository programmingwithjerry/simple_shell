#include "shell.h"




struct Alias aliases[MAX_ALIASES];



/**
 * my_print_all_aliases - prints all defined aliases
 * This function iterates through an array of aliases
 *(likely defined elsewhere)
 * and prints each alias in the format "alias_name='alias_value'".
 * Returns: Nothing (void function).
 */

void our_print_all_aliases(void)
{
	int alias_count = 0;
	int i;

	for (i = 0; i < alias_count; i++)
	{
		isjerry_print("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}


/**
 * my_print_specific_aliases - prints specific aliases
 * based on provided names
 * @names: an array of strings representing alias names to be printed
 * @count: the number of names in the `names` array
 * This function iterates through an array of provided `names`
 * (presumably representing aliases) and searches for matching aliases
 *in an array of defined aliases (`aliases`, likely defined elsewhere).
 *If a match is found, the function prints the alias name and its
 * corresponding value.
 * Returns: Nothing (void function).
 */
void our_print_specific_aliases(char *names[], int count)
{
	int alias_count = 0;
	int i;
	int j;

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < alias_count; j++)
		{
			if (strcmp(names[i], aliases[j].name) == 0)
			{
				isjerry_print("%s='%s'\n", aliases[j].name,
				aliases[j].value);
				break;
			}
		}
	}
}


/**
 * my_define_alias - defines an alias or updates an existing one
 * @name: the name of the alias to be defined or updated
 * @value: the value of the alias
 * This function attempts to define a new alias or update an existing one.
 * It first searches for an alias with the same name in the `aliases` array.
 * If a match is found, the existing value is freed and replaced with the
 *   new value provided in the `value` argument.
 * - If no match is found and the number of defined aliases is less than the
 *   maximum allowed (`MAX_ALIASES`), a new entry is created in the `aliases`
 *   array with the provided `name` and `value`. The
 *`alias_count` is incremented
 *   to reflect the new alias.
 * Returns: Nothing (void function).
 */
void our_define_alias(char *name, char *value)
{
	int alias_count = 0;
	int i;

	for (i = 0; i < alias_count; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			free(aliases[i].value);
			aliases[i].value = strdup(value);
			return;
		}
	}

	if (alias_count < MAX_ALIASES)
	{
		aliases[alias_count].name = strdup(name);
		aliases[alias_count].value = strdup(value);
		alias_count++;
	}
	else

		isjerry_print("Error: Maximum number of aliases reached\n");

}

/* Implementation of the alias builtin command*/
/**
 * my_alias_builtin - handles alias definition and printing
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments (strings)
 * This function handles user interaction with aliases.It checks for the number
 * of arguments and performs operations based on its findings:
 *If no arguments are provided, it prints all currently defined aliases.
 *If arguments are provided:
 *	It iterates through each argument and separates it into name and value
 *      sing the '=' delimiter (`strtok`).
 *	If no value is provided (no '=' found), the argument is considered a name
 *	to print, and it's added to the `print_names` array.
 *	If both name and value are provided, they are passed to the
 *my_define_alias` function to define or update an alias.
 * Returns: Nothing (void function).
 */

void isjerry_alias_builtin(int argc, char *argv[])
{
	int define_count = 0;
	/*char *define_names[MAX_ALIASES];*/
	char *print_names[MAX_ALIASES];
	int i;
	char *name;
	char *value;

	if (argc == 1)
		our_print_all_aliases();
	else
	{

		for (i = 1; i < argc; i++)
		{
			name = strtok(argv[i], "=");
			value = strtok(NULL, "=");

			if (value == NULL)
			{
				print_names[define_count] = strdup(name);
				define_count++;
			}
			else

				our_define_alias(name, value);
		}

		if (define_count > 0)
		{
			/* Print specific aliases*/
			our_print_specific_aliases(print_names, define_count);
		}
	}
}
