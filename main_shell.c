#include "shell_head.h"
/**
 *main - Displays a prompt and user enters a command
 *@arg1 :int val 1
 *@arg2 :array val 2
 *Return: 0 on success
 */
int main(int arg1, char *arg2[])
{

	char **tokens;
	char *line;
	int status;
	struct stat st;
	(void)arg1;
	signal(SIGINT, ctrl_c);
	if (fstat(0, &st) == -1)
		perror("fstat");
	status = 1;
	do { /*print prompt if command is not piped*/
		print();
		line = read_line1(); /*read input from standard input*/
		if (_strcomp(line, "\n") == 0)
		{
			tokens = NULL;
			free(line);
			continue;
		}
		get_hist(line);
		/*split the line into tokens*/
		tokens = _strtok(line);
		if (tokens[0] == NULL)
		{
			free(tokens);
			free(line);
			continue;
		}
		if (_strcomp(tokens[0], "exit") == 0)
		{
			sexit(tokens, line); /*handle exit*/
		}
		else
		{
			status = _exe(tokens, line, arg2[0]);/*execute commands*/
		}
		free(line); /*free memory*/
		free(tokens);
	} while (status == 1);
	return (status);
}
