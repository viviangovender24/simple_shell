#include "shell_head.h"
/**
 *free_a - frees a two dimensional string
 *@args:array of pointers to strings
 *Return:void
 */
void free_a(char **args)
{
	int i = 0;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
}
/**
 *read_line1 - reads user's input from standard input
 *
 *Return:pointer to string containing user input
 */
char *read_line1(void)
{
	char *line = NULL;
	size_t len = 0;
	int v = 0;

	v = getline(&line, &len, stdin);
	if (v == EOF)
	{
		free(line);
		exit(0);
	}
	if (line == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(-1);
	}

	return (line);
}
