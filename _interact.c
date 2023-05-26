#include "shell_head.h"

/**
 * interact - returns true if shell is interactive mode
 * @form: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interact(info_t *form)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _delim - checks if character is a delimeter
 * @b: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _delim(char b, char *delim)
{
	while (*delim)
		if (*delim++ == b)
			return (1);
	return (0);
}

/**
 * _alpha - checks for alphabetic character
 * @f: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int f)
{
	if ((f >= 'a' && f <= 'z') || (f >= 'A' && f <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * c_atoi - converts a string to an integer
 * @d: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int c_atoi(char *d)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; d[i] != '\0' && flag != 2; i++)
	{
		if (d[i] == '-')
			sign *= -1;

		if (d[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
