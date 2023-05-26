#include "shell_head.h"

/**
 * error_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int error_atoi(char *s)
{
	int b = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (b = 0;  s[b] != '\0'; b++)
	{
		if (s[b] >= '0' && s[b] <= '9')
		{
			result *= 10;
			result += (s[b] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
}
	return (result);
}

/**
 * format_error - prints an error message
 * @read: the parameter & return info struct
 * @st: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void format_error(info_t *read, char *st)
{
	_eputs(read->fname);
	_eputs(": ");
	print_d(read->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(read->argv[0]);
	_eputs(": ");
	_eputs(st);
}

/**
 * format_d - function prints a decimal (integer) number (base 10)
 * @puts: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int format_d(int puts, int fd)
{
	int (*__putchar)(char) = _putchar;
	int b, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (puts < 0)
	{
		_abs_ = -puts;
		__putchar('-');
		count++;
	}
	else
		_abs_ = puts;
	current = _abs_;
	for (b = 1000000000; b > 1; b /= 10)
	{
		if (_abs_ / b)
		{
			__putchar('0' + current / b);
			count++;
		}
		current %= b;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * change_number - converter function, a clone of itoa
 * @no: number
 * @base: base
 * @flg: argument flags
 *
 * Return: string
 */
char *change_number(long int no, int base, int flg)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = no;

	if (!(flg & CHANGE_UNSIGNED) && no < 0)
	{
		n = -no;
		sign = '-';

	}
	array = flg & CHANGE_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * delete_comments - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void delete_comments(char *buff)
{
	int b;

for (b = 0; buff[b] != '\0'; b++)
if (buff[b] == '#' && (!b || buff[b - 1] == ' '))
		{
buff[b] = '\0';
			break;
		}
}
