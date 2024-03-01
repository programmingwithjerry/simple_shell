#include "shell.h"

/**
 * execute_path_command - executes a command based on the PATH
 *environment variable
 * @command: the command name to be executed
 * This function attempts to execute a command by searching for it along the
 * directories specified in the `PATH` environment variable. It creates a child
 * process, sets up a pipe for communication, and searches for the command in
 * different directories. If found, it replaces the child process's standard
 * output with the pipe's write end and executes the command. Otherwise, it
 * prints an error message.
 * Returns:
 *   - Nothing (void function).
 */


void execute_path_command(const char *command)
{
	pid_t pid;
	int status;
	int fd[2];
	char buffer[1024], *token, *command_copy, *path, *path_copy, *dir;
	ssize_t nbytes;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{ /* Child process*/
		close(fd[0]); /*Close read end of pipe*/
		dup2(fd[1], STDOUT_FILENO); /* Redirect stdout to pipe write end*/
		close(fd[1]); /* Close write end of pipe*/
		command_copy = strdup(command);
		token = strtok(command_copy, " ");
		path = getenv("PATH");
		path_copy = strdup(path);
		dir = strtok(path_copy, ":");
		while (dir != NULL)
		{
			char *full_command_path = malloc(strlen(dir) + strlen(token) + 2);

			strcpy(full_command_path, dir);
			strcat(full_command_path, "/");
			strcat(full_command_path, token);
			if (access(full_command_path, X_OK) == 0)
			{
				char **argv = malloc(sizeof(char *) * 2);

				argv[0] = token;
				argv[1] = NULL;
				execve(full_command_path, argv, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free(full_command_path);
			dir = strtok(NULL, ":");
		}
		printf("Command not found: %s\n", token);
		free(command_copy);
		free(path_copy);
		exit(EXIT_FAILURE);
	}
	else
	{ /*Parent process*/
		close(fd[1]); /*Close write end of pipe*/
		while ((nbytes = read(fd[0], buffer, sizeof(buffer))) > 0)
			write(STDOUT_FILENO, buffer, nbytes); /*Write output to stdout*/

		close(fd[0]); /*Close read end of pipe*/

		waitpid(pid, &status, 0); /*Wait for child process to finish*/
	}
}
