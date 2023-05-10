#include "shell_head.h"

/**
 * _reallocate - allocate memory and set all values to 0
 * @ptr: pointer to the memory previously allocated (malloc(old_si))
 * @old_si: size previously allocated
 * @new_si: new size to reallocate
 * Return: pointer to reallocated memory
 */

void *_reallocate(void *ptr, unsigned int old_si, unsigned int new_si)
{
	void *p;
	unsigned int i;

	if (new_si == 0 && ptr != NULL) /* free memory if reallocate 0 */
	{
		free(ptr);
		return (NULL);
	}

	if (new_si == old_si) /* return ptr if reallocating same old size */
		return (ptr);

	if (ptr == NULL) /* malloc new size if ptr is originally null */
	{
		p = malloc(new_si);
		if (p == NULL)
			return (NULL);
		else
			return (p);
	}

	p = malloc(new_si); /* malloc and check error */
	if (p == NULL)
		return (NULL);

	/* fill up values up till minimum of old or new size */
	for (i = 0; i < old_si && i < new_si; i++)
		*((char *)p + i) = *((char *)ptr + i);
	free(ptr); /* free old ptr */

	return (p);
}
