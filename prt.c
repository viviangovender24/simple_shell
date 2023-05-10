#include "shell_head.h"

/**
 *get_path - gets the absolute path of a command
 *@args:pointer to an array of strings
 *Return:address of the path
 */
int get_path(char **args)
{
	char *path, *tok, *cmd_tok;
	struct stat st;

	path = get_enviro("PATH");
	tok = strtok(path, ":");

	while (tok != NULL)
	{
		cmd_tok = build(*args, tok);
		if (stat(cmd_tok, &st) == 0)
		{
			*args = _strdupli(cmd_tok);
			free(cmd_tok);
			free(path);
			return (0);
		}
		free(cmd_tok);
		tok = strtok(NULL, ":");
	}
	free(path);
	return (1);
}
/**
 *get_enviro - retrieves an environment variable
 *@path:variable passed
 *Return:pointer to a string
 */
char *get_enviro(char *path)
{
	char *envcopy;
	int i = 0;
	int len, len2;

	while (environ[i])
	{
		len = _strlen(path);
/*locate substring PATH*/
		if (strstr(environ[i], path))
		{
			if (environ[i][len] == '=')
			{
				len2 = _strlen(environ[i]) - _strlen(path);
				envcopy = malloc(sizeof(char) * len2);
				if (envcopy == NULL)
				{
					perror("Error: Insufficient memory");
					exit(1);
				}
				_strcopy(envcopy, environ[i] + (len + 1));
				return (envcopy);
			}
		}
		i++;
	}
	return (NULL);
}
/**
 *cmdbuild - returns full cmd path
 *@token:cmd passed
 *@dir:current path dir
 *Return:pointer to full cmd path
 */
char *cmdbuild(char *token, char *dir)
{
	size_t path_len;
	char *path;

	path_len = _strlen(token) + _strlen(dir) + 2;
	path = malloc(sizeof(char) * path_len);

	if (path == NULL)
	{
		perror("Error: malloc->buildcmd\n");
		return (NULL);
	}
	memset(path, 0, path_len);

	path = _strjoin(path, dir);
	path = _strjoin(path, "/");
	path = _strjoin(path, token);
	return (path);
}
