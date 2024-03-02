#include "shell.h"



int main(int argc, char *argv[]) {
	char *input = NULL;
	size_t input_size = 0;
	int i, alias_count = 0;

	while(1)
	{
		prompt_user();
		execute_exit_command();
		get_command(input, input_size);
		our_get_command(input, input_size);
		execute_path_command("/bin/ls");
		execute_path_command("ls -l /tmp");
		execute_command(input);
		execute_command("/bin/ls");
		execute_command("ls -l");

		isjerry_print("Enter commands separated by ';':\n");
		if (getline(&input, &input_size, stdin) == -1) {
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}

		*my_semicolon_handler(input);
		isjerry_semicolon_handler(input);
		my_or_handler(input);
		isjerry_or_handler(input);
		isjerry_alias_builtin(argc, argv);
		alias_builtin(argc, argv);
		for (i = 0; i < alias_count; i++) {
			free(aliases[i].name);
			free(aliases[i].value);
		}

		if (argc != 2) {
			perror("Usage: VARIABLE");
			return 1;
		}

		if (our_unsetenv_builtin(argv[1]) != 0) {
			return 1;
		}

		isjerry_print("Environment variable %s unset\n", argv[1]);

		if (argc != 3) {
			perror("Usage: VARIABLE VALUE");
			return 1;
		}

		if (isjerry_setenv_builtin(argv[1], argv[2]) != 0) {
			return 1;
		}

		isjerry_print("Environment variable %s set to %s\n", argv[1], argv[2]);

		free(input);
	}

	return 0;
}

/**
*int main(int argc, char *argv[])
*{
*	char *input = NULL;
*	size_t input_size = 0;
*
*	while(1)
*	{
*		prompt_user();
*		if (getline(&input, &input_size, stdin) == -1)
*		{
*			perror("Error reading input");
*			exit(EXIT_FAILURE);
*		}
*		parse_and_execute(input);
*		free(input);
*	}
*
*	return (0);
*}
*
*void parse_and_execute(char *input)
*{
*	if (strstr(input, "exit") != NULL)
*	{
*		execute_exit_command();
*	}
*	else if (strstr(input, "our_get_command") != NULL)
*	{
*		our_get_command(input, input_size);
*	}
*	else if (strstr(input, "execute_path_command") != NULL)
*	{
*
*		execute_path_command(input);
*	}
*	else if (strstr(input, "execute_command") != NULL)
*	{
*		execute_command(input);
*	}
*	else if (strstr(input, "isjerry_semicolon_handler") != NULL)
*		isjerry_semicolon_handler(input);
*	}
*	else if (strstr(input, "isjerry_or_handler") != NULL)
*	{
*		isjerry_or_handler(input);
*	}
*	else if (strstr(input, "isjerry_alias_builtin") != NULL)
*	{
*		isjerry_alias_builtin(argc, argv);
*	}
*	else if (strstr(input, "unsetenv") != NULL)
*	{
*		execute_unsetenv_command(argv);
*	}
*	else if (strstr(input, "setenv") != NULL)
*	{
*		execute_setenv_command(argv);
*	}
*	else
*	{
*		isjerry_print("Unrecognized command: %s\n", input);
*	}
*}
*
*void execute_exit_command()
*{
*	exit(EXIT_SUCCESS);
*}
*
*void execute_unsetenv_command(char *argv[])
*{
*	if (argc != 2)
*	{
*		perror("Usage: VARIABLE");
*		return (1);
*	}
*
*	if (our_unsetenv_builtin(argv[1]) != 0)
*	{
*		return (1);
*	}
*
*	isjerry_print("Environment variable %s unset\n", argv[1]);
*}
*
*void execute_setenv_command(char *argv[])
*{
*	if (argc != 3)
*	{
*		perror("Usage: VARIABLE VALUE");
*		return (1);
*	}
*
*	if (isjerry_setenv_builtin(argv[1], argv[2]) != 0)
*	{
*		return (1);
*	}
*
*	isjerry_print("Environment variable %s set to %s\n", argv[1], argv[2]);
*}
*/
