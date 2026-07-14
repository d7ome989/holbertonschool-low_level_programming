#include "main.h"

/**
 * puts_half - prints half of a string, followed by a new line
 * @str: the string to be printed
 *
 * Return: void
 */
void puts_half(char *str)
{
	int len;
	int start;
	int i;

	for (len = 0; str[len] != '\0'; len++)
	{
	}

	start = len / 2;
	if (len % 2 != 0)
	{
		start = start + 1;
	}

	for (i = start; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
	_putchar('\n');
}
