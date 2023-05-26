#include "shell_head.h"

/**
 * _egress - exits the shell
 * @read: Struct containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if read.argv[0] != "exit"
 */
int _egress(info_t *read)
{
	int pullout;

	if (read->argv[1]) /* If there is an exit arguement */
	{
		pullout = _erratoi(read->argv[1]);
		if (pullout == -1){
			read->status = 2;
			print_error(read, "Illegal number: ");
			_eputs(read->argv[1]);
			_eputchar('\n');
			return (1);
		}
		read->err_num = _erratoi(read->argv[1]);
		return (-2);
	}
	read->err_num = -1;
	return (-2);
}

/**
 * _currentcd - changes the current directory of the process
 * @read: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _currentcd(info_t *read)
{
	char *d, *dir, buffer[1024];
	int chdir_ret;

	d = getcwd(buffer, 1024);
	if (!d)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!read->argv[1])
	{
		dir = _getenv(read, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(read, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(read->argv[1], "-") == 0)
{
		if (!_getenv(read, "OLDPWD="))
		{
			_puts(d);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(read, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(read, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(read->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(read, "can't cd to ");
		_eputs(read->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(read, "OLDPWD", _getenv(read, "PWD="));
		_setenv(read, "PWD", getcwd(buffer, 1024));
}
	return (0);
}

/**
 * _change - changes the current directory of the process
 * @read: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _change(info_t *read)
{
	char **arg_array;

	arg_array = read->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
