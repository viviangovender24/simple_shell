#include "shell.h"

/**
 * _lengthlist - determines length of linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t _lengthlist(const list_ *p)
{
	size_t b = 0;

	while (p)
	{
		p = p->next;
		b++;
	}
	return (b);
}

/**
 * _stringlist - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **_stringlist(list_ *head)
{
	list_ *node = head;
	size_t b = _lengthlist(head), j;
	char **strs;
	char *str;

	if (!head || !b)
		return (NULL);
	strs = malloc(sizeof(char *) * (b + 1));
	if (!strs)
		return (NULL);
	for (b = 0; node; node = node->next, b++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < b; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[b] = str;
	}
	strs[b] = NULL;
	return (strs);
}


/**
 * _prtlist - prints all elements of a list_t linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t _prtlist(const list_ *p)
{
	size_t b = 0;

	while (p)
	{
		_puts(change_number(p->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(p->str ? p->str : "(nil)");
		_puts("\n");
		p = p->next;
		b++;
	}
	return (b);
}

/**
 * node_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @f: the next character after prefix to match
 *
 * Return: match node or null
 */
list_ *node_start(list_ *node, char *prefix, char f)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((f == -1) || (*p == f)))
			return (node);
		node = node->next; }
	return (NULL);
}

/**
 * node_idx - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_idx(list_ *head, list_t *node)
{
	size_t b = 0;

	while (head)
	{
		if (head == node)
			return (b);
		head = head->next;
		b++;
	}
	return (-1);
}
