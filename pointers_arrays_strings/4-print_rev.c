#include "main.h"
/**
 * print_rev - print a string but rev
 * @s: the string  want to print revrens
 *
 *
 * Return: void
 *
 *
 */
void print_rev(char *s)
{
	int len;
	int i;

	for (len = 0; s[len] != '\0'; len++)
	{
	}

	for (i = len - 1; i >= 0; i--)
	{
		_putchar(s[i]);
	}
	_putchar('\n');
}
