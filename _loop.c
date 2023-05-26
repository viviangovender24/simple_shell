#include "shell_head.h"

/**
 * hsh - main shell loop
 * @read: the parameter & return info struct
 * @arv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *read, char **arv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(read);
		if (interactive(read))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(read);
		if (r != -1)
		{
			set_info(read, arv);
			builtin_ret = find_builtin(read);
			if (builtin_ret == -1)
				find_cmd(read);
		}
		else if (interactive(read))
			_putchar('\n');
		free_info(read, 0);}
	write_history(read);
	free_info(read, 1);
	if (!interactive(read) && read->status)
		exit(read->status);
	if (builtin_ret == -2)
	{
		if (read->err_num == -1)
			exit(read->status);
		exit(read->err_num);
	}
	return (builtin_ret);
}

/**
 * get_builtin - finds a builtin command
 * @read: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int get_builtin(info_t *read)
{
	int b, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"same", _myalias},
		{NULL, NULL}
	};

	for (b = 0; builtintbl[i].type; b++)
		if (_strcmp(read->argv[0], builtintbl[b].type) == 0)
		{
			read->line_count++;
			built_in_ret = builtintbl[b].func(read);
			break;
		}
	return (built_in_ret);
}

/**
 * get_cmd - finds a command in PATH
 * @read: the parameter & return info struct
 *
 * Return: void
 */
void get_cmd(info_t *read)
{
	char *path = NULL;
	int b, k;

	read->path = read->argv[0];
	if (read>linecount_flag == 1)
	{
		read->line_count++;
		read->linecount_flag = 0;
	}
	for (b = 0, k = 0; read->arg[b]; b++)
		if (!_delim(read->arg[b], " \t\n"))
			k++;
if (!k)
		return;

	path = get_path(read, _getenv(read, "PATH="), ->argv[0]);
	if (path)
	{
		read->path = path;
		fork_cmd(read);
	}
	else
	{
		if ((interactive(read) || _getenv(read, "PATH=")
					|| read->argv[0][0] == '/') && cm_d(read, read->argv[0]))
			fork_cmd(read);
		else if (*(read->arg) != '\n')
		{
			read->status = 127;
			get_error(read, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @read: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *read)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(read->path, read->argv, get_environ(read)) == -1)
{
			free_info(read, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(read->status));
		if (WIFEXITED(read->status))
		{
			read->status = WEXITSTATUS(read->status);
			if (read->status == 126)
				print_error(read, "Permission denied\n");
		}
	}
}
