#include "shell.h"


int main(int argc, char *argv[]) {
	char *input = NULL;
	size_t input_size = 0;
	int i, alias_count = 0;

	while(1)
	{
		prompt_user();
		execute_exit_command();
		/*get_command(input, input_size);*/
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

		/*my_semicolon_handler(input);*/
		isjerry_semicolon_handler(input);
		/*my_or_handler(input);*/
		isjerry_or_handler(input);
		isjerry_alias_builtin(argc, argv);
		/*alias_builtin(argc, argv);*/

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
