#include "shell-head.h"

/**
 **_strncpy - copies a string
 *@dn: the destination string to be copied to
 *@sc: the source string
 *@m: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *dn, char *sc, int m)
{
	int b, j;
	char *d = dn;

	b = 0;
	while (sc[b] != '\0' && b < m - 1)
	{
		dn[b] = sc[b];
		b++;
	}
	if (b < m)
	{
		j = b;
		while (j < m)
		{
			dn[j] = '\0';
			j++;
		}
}
	return (d);
}

/**
 **_strncat - concatenates two strings
 *@dn: the first string
 *@sc: the second string
 *@m: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dn, char *sc, int m)
{
	int b, j;
	char *d = dn;

	b = 0;
	j = 0;
	while (dn[b] != '\0')
		b++;
	while (sc[j] != '\0' && j < m)
	{
		dn[b] = sc[j];
		b++;
		j++;
	}
	if (j < m)
		dn[b] = '\0';
return (b);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@f: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char f)
{
	do {
		if (*s == f)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
