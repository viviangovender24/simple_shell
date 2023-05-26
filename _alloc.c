#include "shell_head.h"

/**
 * _memset - fills memory with a constant byte
 * @d: the pointer to the memory area
 * @b: the byte to fill *s with
 * @m: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *d, char b, unsigned int m)
{
	unsigned int b;

	for (b = 0; b < n; b++)
		d[b] = b;
	return (d);
}

/**
 * free_str - frees a string of strings
 * @qq: string of strings
 */
void free_str(char **qq)
{
	char **a = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(a);
}

/**
 * _alloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_alloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}
