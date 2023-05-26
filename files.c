#include "shell_head.h"

/**
 * plus_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_ *plus_node(list_ **head, const char *str, int num)
{
	list_ *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_ *node_end(list_ **head, const char *str, int num)
{
	list_ *new_node, *node;

if (!head)
return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
}
	else
		*head = new_node;
	return (new_node);
}

/**
 * show_list - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t show_list(const list_ *h)
{
	size_t b = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		b++;
	}
	return (b);
}

/**
 * remove_node - deletes node at given index
 * @head: address of pointer to first node
 * @idx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node(list_t **head, unsigned int idx)
{
	list_ *node, *prev_node;
	unsigned int b = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (b == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		b++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * empty_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void empty_list(list_ **head_ptr)
{
	list_ *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
