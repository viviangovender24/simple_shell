#include "shell_head.h"

/**
 * _strjoin - concatenate two strings
 * @st1: string to be appended to
 * @st2: string to append
 * Return: concatenated string
 */
char *_strjoin(char *st1, char *st2)
{
	int len = 0;
	int len2 = 0;
	int tot_len = 0;
	int j = 0;

	/* find total length of both string */
	while (st1[len] != '\0')
	{
		len++;
		tot_len++;
	}
	while (st2[len2] != '\0')
	{
		len2++;
		tot_len++;
	}

	/* memory */
	st1 = _reallocate(st1, len, sizeof(char) * tot_len + 1);

	while (st2[j] != '\0')
	{
		st1[len] = st2[j];
		len++;
		j++;
	}
	st1[len] = '\0';

	return (st1);
}
/**
 * _strcomp - compare two strings
 * @s1: string 1
 * @s2: string 2
 * Return: int that tells num spaces in between, 0 if exactly the same string
 */

int _strcomp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i] && s1[i])
		i++;

	if (s2[i])
		return (s1[i] - s2[i]);
	else
		return (0);
}

/**
 * _strcopy - copies the string pointed to by str,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @str: this is the source to copy
 * Return: copy of original source
 */

char *_strcopy(char *dest, char *str)
{
	int i, len;

	for (len = 0; str[len] != '\0'; len++)
		;

	for (i = 0; i <= len; i++)
		dest[i] = str[i];

	return (dest);
}

/**
 * _strdupli - returns a pointer to a new space in memory,
 * which contains a copy of the string given as parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string
 */
char *_strdupli(char *str)
{
	char *duplicate;
	int i, len = 0;

	if (str == NULL) /* validate input */
		return (NULL);

	while (str[len])
		len++;
	len++; /* add null (end) to length */

	duplicate = malloc(sizeof(char) * len); /* allocate memory */
	if (duplicate == NULL)
		return (NULL);

	i = 0;
	while (i < len)
	{
		duplicate[i] = str[i];
		i++;
	}

	return (duplicate);
}

/**
 * _strlen - find the length of a string
 * @str: pointer to the string
 * Return: characters in the string
 */
int _strlen(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}
