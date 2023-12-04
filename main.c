#include "shell.h"

/**
 * main - the entry point to shell
 * @ac: the arguments count
 * @av: the argument vector
 * Return: Return 0 if successful, else 1 on error
 */
int main(int ac, char **av)
{
	/* Initialize info_t array with a single element */
	info_t info[] = { INFO_INIT };
	/* Set fd variable to 2 */
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
	/* Check if there are exactly 2 command-line arguments */
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			/* Handle specific errors */
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				/* Print error message and exit with status 127 */
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			/* Return EXIT_FAILURE for general open error */
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	/* Execute the shell with the provided arguments */
	hsh(info, av);
	/* Return EXIT_SUCCESS upon successful execution */
	return (EXIT_SUCCESS);
}
