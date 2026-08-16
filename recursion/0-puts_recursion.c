#include "main.h"

/**
 * _puts_recursion - prints a string followed by a new line, recursively
 * @s: the string to print
 *
 * Return: void
 */
void _puts_recursion(char *s)
{
	static int i;

	if (s[i] == '\0')
	{
		_putchar('\n');
		i = 0;
		return;
	}

	_putchar(s[i]);
	i++;
	_puts_recursion(s);
}
