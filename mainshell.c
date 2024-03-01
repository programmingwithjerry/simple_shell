#include "mshell.h"

int main(void) {
	char prompt_command[128];
	char *arguments[MAX_ARGS];
	while (1) {
		print_prompt();
		read_cmd(prompt_command, sizeof(prompt_command));
		if (strcmp(prompt_command, "exit") == 0){
			break;
		}
		
		tokenize_input(prompt_command, arguments);
		if (arguments[0] != NULL) {
			exec_command(arguments[0], arguments);
		}
	}
	return (0);
}
