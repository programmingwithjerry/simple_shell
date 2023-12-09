#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential args.
 * Used to maintain constant function prototype.
 * Return: exits with a given exit status
 *  (0) if info.argv[0] != "exit"
 */

int _myexit(info_t *info)
{
	int exitcheck;

	/* If there is an exit arguement */
	if (info->argv[1])
	{
		/* If exit argument is not a valid integer */
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			/* Set error number and return */
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	/* No exit argument provided */
	info->err_num = -1;
	return (-2);
}


/**
 * _mycd - This changes current directory of the process
 * @info: Struct containing potential args. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024); /* Get the current working directory */
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		/* If OLDPWD is not set, print current directory */
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1) /* Handle chdir failure */
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}



/**
 * _myhelp - to change the current directory of the process
 * @info: Struct containing potential args. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	/* Display a message indicating the help call works */
	_puts("help call works. Function not yet implemented \n");

	/*
	* Temporary workaround for unused variable warning.
	* Display the first argument in the argument array.
	*/
	if (0)
		_puts(*arg_array);
	return (0);
}
