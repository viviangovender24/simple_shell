#include "shell_head.h"

/**
 *print - displays promt before user input
 *
 *Return:void
 */
void print(void)
{
	if (isatty(STDIN_FILENO))
	{
		_print("#teamShell$ ");
	}
}
/**
 *ctrl_c - suppresses quitting when Ctrl c is invoked
 *@num:SIGINT variable
 *Return:void
 */
void ctrl_c(int num)
{
	(void)num;
	signal(SIGINT, ctrl_c);
	write(STDIN_FILENO, "\n#teamShell$ ", 11);
}
/**
 *sexit - exits a shell
 *@args:arguements passed
 *@line:string to free
 *Return:void
 */
void sexit(char **args, char *line)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
		if (status >= 0)
		{
			free(line);
			free(args);
			exit(status);
		}
		printf("Exit: illegal status: %s\n", args[1]);
	}
	else
	{
		free(line);
		free(args);
		exit(0);
	}
}
