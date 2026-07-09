#include "main.h"
#include <stdio.h>
/**
 * print_alphabet - Prints the alphabet in lowercase, followed by a new line
 * Return: void
 */
void print_alphabet_x10(void)
{
	int n;

	for (n = 1; n <= 10; n++)
	{
		print_alphabet();
		_putchar('\n');
	}
	_putchar('\n');
}
