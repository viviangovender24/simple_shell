#include "shell_head.h"

/**
 * g_environ - returns the string array copy of our environ
 * @read: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **g_environ(info_t *read)
{
	if (!read->environ || read->env_changed)
	{
		read->environ = list_to_strings(read->env);
		read->env_changed = 0;
	}

	return (read->environ);
}

/**
 * unset_env - Remove an environment variable
 * @read: Structure containing potential arguments. Used to maintain
 *        constant function prototype
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_env(info_t *read, char *var)
{
	list_ *node = read->env;
	size_t b = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			read->env_changed = delete_node_at_index(&(read->env), b);
			b = 0;
			node = read->env;
			continue;
		}
		node = node->next;
		b++;
	}
	return (read->env_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @read: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int set_env(info_t *read, char *var, char *val)
{
	char *buf = NULL;
	list_ *node;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = read->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			read->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(read->env), buf, 0);
	free(buf);
	read->env_changed = 1;
	return (0);
}
