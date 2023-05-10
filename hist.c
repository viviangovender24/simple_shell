#include "shell_head.h"
/**
 *get_hist - fills file with user input
 *@input:user input
 *Return:0 - success,-1 otherwise
 */
int get_hist(char *input)
{
	int len = 0;
	ssize_t fd;
        ssize_t w;
	char *file_name = "/.simple_shell_history";
	char *directory = get_enviro("HOME");
	char *file_path = malloc(_strlen(directory) + _strlen(file_name) + 1);
	if (!file_path)
	{
		perror("malloc error->get_history");
		free(directory);
		return (-1);
	}
	_strcopy(file_path, directory);
	_strcopy(file_path, file_name);

/*if not exist create,read and write and append if exist*/
	fd = open(file_path, O_CREAT | O_RDWR | O_APPEND, 0600);
	if (fd < 0)
		return (-1);
	if (input)
	{
		while (input[len])
			len++;
		w = write(fd, input, len);
		if (w < 0)
			return (-1);
	}
	free(file_path);
	free(directory);
	return (1);
}
/**
 *display_history - displays user's history
 *
 *Return:0 (success), -1 otherwise
 */
int display_history(void)
{
	char *file_name = "/.simple_shell_history";
	char *directory = get_enviro("HOME");
	char *file_path = malloc(_strlen(file_name) + _strlen(directory) + 1);
	char *line = NULL;
	size_t len;
	FILE *fp;
	int counter = 0;
	if (!file_path)
	{
		perror("malloc error->display_history");
		free(directory);
		return (-1);
	}
	_strcopy(file_path, directory);
	_strcopy(file_path, file_name);
	fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		printf("%d %s", counter, line);
	}
	if(line != NULL)
		free(line);
	fclose(fp);
	free(file_path);
	free(directory);
	return (0);
}
