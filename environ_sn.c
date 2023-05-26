#include "shell.h"

/**
 * env_now - prints the current environment
 * @read: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_now(info_t *read)
{
	print_list_str(read->now);
	return (0);
}

/**
 * env_open - gets the value of an environ variable
 * @read: Structure containing potential arguments. Used to maintain
 * @call: env var name
 *
 * Return: the value
 */
char *env_open(info_t *read, const char *call)
{
	list_ *node = read->now;
	char *p;

	while (node)
	{
		p = starts_with(node->str, call);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @read: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int set_env(info_t *read)
{
	if (read->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(read, read->argv[1], read->argv[2]))
		return (0);
	return (1);
}
/**
 * unset_env - Remove an environment variable
 * @read: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_env(info_t *read)
{
	int b;

	if (read->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (b = 1; b <= read->argc; b++)
		unset_env(read, read->argv[b]);

	return (0);
}

/**
 * fill_list - populates env linked list
 * @read: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int fill_list(info_t *read)
{
	list_ *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	read->now = node;
	return (0);
}
