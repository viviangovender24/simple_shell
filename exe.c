#include "shell_head.h"

/**
 * _occur - return the number of occurence of a string
 * @s: string to check
 * Return: integer
 */
unsigned int _occur(char *s)
{
	int i, count = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		/*test for delimeters*/
		if (s[i]  == ' ' || s[i] == '\t' || s[i] == '\n')
			count++;
	}

	return (count);
}
/**
 *_strtok - split a sentence into multiple words.
 *@str: the string passed as argument.
 *Return: tokens
 */
char **_strtok(char *str)
{
	int i = 0;
	const char separator[] = " \t\n";
	int spaces = _occur(str);
	char **tokens = malloc(sizeof(char *) * (spaces + 1));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "sh: allocation error\n");
		exit(1);
	}

	token = strtok(str, separator);

	while (token != NULL)
	{
		tokens[i] = token;
		token = strtok(NULL, separator);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
/**
 *file_status - checks whether a file exists
 *@filename:name of file
 *Return:0 - file is available, -1 otherwise
 */
int file_status(char *filename)
{
	struct stat st1;

	if (stat(filename, &st1) == -1)
		return (-1);
	return (0);
}
/**
 *_exe - executes a file given as input
 *@tok:split tokens from stdin input
 *@line:line from stdin to free
 *Return:-1 (success), -1,otherwise
 */
int _exe(char **tok, char *line, char *args)
{
	char *er1, *er2, *er3;
	pid_t cpid;
	int staytus;
	struct stat st;

	/*token  a builtin cmd or NULL*/
	if (parser(tok) == 0 || *tok == NULL)
	{
		return (1);
	}
	/*fork the process*/
	cpid = fork();
	if (cpid < 0)
	{
		perror("Error:fork->-1");
		return (EXIT_FAILURE);
	}
/*child process*/
	if (cpid == 0)
	{
		if (stat(*tok, &st) != 0)
		{
			get_path(tok);
		}
		if (execve(tok[0], tok, NULL) == -1)
		{
			er1 = strcat(*tok, ": No such file or directory\n");
			er2 = strcat(args, ":");
			er3 = strcat(er2, er1);
			write(STDERR_FILENO, er3, _strlen(er3));
			/*free(er1);*/
			/*free(er2);*/
			/*free(er3);*/
			free(line);
			free(tok);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
wait(&staytus);
return (1);
}
