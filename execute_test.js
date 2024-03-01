#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/*#include "shell.h"*/


/**
 * execute_command - executes a given command
 * @command: the command string to be executed

 * This function attempts to execute a given command by creating a child
 * process, preparing the arguments, and using `execve` to replace the child
 * process with the desired program. The parent process waits for the child
 * to finish before continuing.

 * Returns:
 *   - Nothing (void function).
 */


void execute_command(const char *command)
{
	pid_t child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		/* Child process*/
		const char *args[2];
		args[0] = command;
		args[1] = NULL;


		/*char *args[] = {command, NULL};*/
		if (execve(command, (char * const *)args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*Parent process*/
		wait(NULL);
	}
}







/**
 *handleCommandLine - prints information about command-line arguments
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments (strings)

 * This function takes the number of arguments (`argc`) and an array of
 * argument strings (`argv`) passed to the program. It then prints information
 * about these arguments, including the total number, the program name (first
 * argument), and each individual argument.

 * Returns: Nothing (void function).
 */


void handle_commands(char *input)
{
	char *command = strtok(input, ";");
	while (command != NULL) {
		execute_command(command);
		command = strtok(NULL, ";");
	}
}

int main() {
	char *input = NULL;
	size_t input_size = 0;

	printf("Enter commands separated by ';':\n");
	if (getline(&input, &input_size, stdin) == -1) {
		perror("Error reading input");
		exit(EXIT_FAILURE);
	}

	handle_commands(input);

	free(input);
	return 0;
}
