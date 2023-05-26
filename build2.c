#include "shell_head.h"

/**
 * _past -displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @read: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _past(info_t *read)
{
	print_list(read->past);
	return (0);
}

/**
 * unset_anonym - sets alias to string
 * @read: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_(info_t *read, char *str)
{
	char *p, f;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	f = *p;
	*p = 0;
	ret = delete_node_at_index(&(read->anonym),
		get_node_index(read->anonym, node_starts_with(read->anonym, str, -1)));
	*p = f;
	return (ret);
}

/**
 * set_anonym - sets alias to string
 * @read: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_anonym(info_t *read, char *str)
{
char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_anonym(read, str));

	unset_anonym(read, str);
	return (add_node_end(&(read->alias), str, 0) == NULL);
}

/**
 * print_anonym - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_anonym(list_ *node)
{
	char *p = NULL, *a = NULL;

	if (node)
{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _mycopy - mimics the alias builtin (man alias)
 * @read: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycopy(info_t *read)
{
	int b = 0;
	char *p = NULL;
	list_ *node = NULL;

	if (read->argc == 1)
	{
		node = read->anonym;
		while (node)
		{
print_anonym(node);
			node = node->next;
		}
		return (0);
	}
	for (b = 1; read->argv[b]; b++)
	{
		p = _strchr(read->argv[b], '=');
		if (p)
			set_anonym(read, read->argv[b]);
		else
			print_alias(node_starts_with(read->alias, read->argv[b], '='));
	}

	return (0);
}
