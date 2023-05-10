#include "shell_head.h"
#include <string.h>
#include <stdlib.h>
/**
 *shell_environment - prints environment variables when environment is used
 *
 *Return:1 on success
 */
int shell_environment(void)
{
	int i = 0;

	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (1);
}

/**
 *_sete - adds an environment variable
 *@name:variable name
 *@value:variable value
 *Return:0 - success,otherwise -1
 */
int _sete(char *name, char *value)
{
	int i = 0;
	size_t name_len;
	char *new;

	name_len = _strlen(name);
	i = 0;
	/*update existing variable*/
	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0)
		{
			new = build(name, value);
			/*Not sure but wanted to clear its mem b4 writing*/
			environ[i] = NULL;
			environ[i] = _strdupli(new);
			free(environ[i]);
			environ[i] = _strdupli(new);
			free(new);
			return (0);
		}
		i++;
	}
	/*adding new variable*/
	new = build(name, value);
	free(environ[i]);
	environ[i] = _strdupli(new);
	i++;
	environ[i] = NULL;
	new = NULL;

	return (0);
}
/**
 *build - builds an environment variable
 *@name:variable name
 *@value:variable value
 *Return:string containing full environment variable
 */
char *build(char *name, char *value)
{
	char *new_var;
	size_t len;

	len = _strlen(name) + _strlen(value) + 2;
	new_var = malloc(sizeof(char) * len);
	if (new_var == NULL)
	{
		perror("Error: Insufficient memory\n");
		return (NULL);
	}
	memset(new_var, 0, len);

	/*name=value*/
	new_var = _strjoin(new_var, name);
	new_var = _strjoin(new_var, "=");
	new_var = _strjoin(new_var, value);

	return (new_var);
}


/**
 *_unsete - removes an environment variable
 *@name:variable name
 *Return:0 if successful -1,otherwise
 */
int _unsete(char *name)
{
	int i = 0;
	char **temp;
	size_t name_len;

	name_len = _strlen(name);
	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0)
		{
			temp = environ;
			free(temp[0]);
			do {
				temp[0] = temp[1];
				temp++;
			} while (*temp);
		}
		i++;
	}
	return (0);
}
