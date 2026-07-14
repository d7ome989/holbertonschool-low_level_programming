#include "main.h"

/**
 * puts2 - print a string
 * @str: the string  want to print
 *
 *
 * Return: void
 *
 *
 */
void puts2(char *str)
{
	int i;
	int len;

	for (len = 0; str[len] != '\0'; len++)
	{
	}

	for (i = 0; len > i; i += 2)
	{

		_putchar(str[i]);
	}
	_putchar('\n');
}
