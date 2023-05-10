#include "shell_head.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
return (write(1, &ch, 1));
}

/**
 * _print - prints a string
 * @str: pointer to the string to print
 * Return: void
 */
void _print(char *str)
{
int i = 0;
while (str[i])
{
_putchar(str[i]);
i++;
}
}
