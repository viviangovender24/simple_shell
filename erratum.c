#include "shell_head.h"

/**
 * _input - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _input(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_inputchar(str[i]);
		i++;
	}
}

/**
 * _char - writes the character c to stderr
 * @f: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _char(char f)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (f == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (f != BUF_FLUSH)
		buf[i++] = f;
	return (1);
}

/**
 * _writefd - writes the character c to given fd
 * @f: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writefd(char f, int fd)
{
	static int i;
static char buf[WRITE_BUF_SIZE];

	if (f == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (f != BUF_FLUSH)
		buf[i++] = f;
	return (1);
}

/**
 * _writesfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _writesfd(char *str, int fd)
{
	int i = 0;
if (!str)
return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
