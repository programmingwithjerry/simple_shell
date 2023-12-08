#include "shell.h"

/**
 * hsh -The main shell loop
 * @info: parameter & return information structure
 * @av: arg vector from main()
 * Return: 0 if successful, 1 on error, or if error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	 /* Main shell loop */
	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		 /* Process input if it is not EOF */
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		/* Handle interactive mode newline */
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	/* Exit the shell with the specified error code */
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	/* Return the exit status or error code */
	return (builtin_ret);
}

/**
 * find_builtin - To find a builtin command
 * @info: the parameter & return info structure
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int index, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[index].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - searchs a command in PATH
 * @info: the parameter & return information structure
 * Return: nothing
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	/* Set the initial path to the command */
	info->path = info->argv[0];
	/* Increment line count if linecount_flag is set */
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	/* Find the full path to the command executable */
	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		/* If the command is not found, print an error message */
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an executable thread to run cmd
 * @info: the parameter & return information structure
 * Return: nothing
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	/* Fork a new process */
	child_pid = fork();
	/* Check for fork failure */
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		/* Execute the command in the child process */
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			/* Check for permission denied error */
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			/* Print an error message for permission denied */
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
