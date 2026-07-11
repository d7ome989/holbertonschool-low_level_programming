#include "main.h"
/**
 * print_line - print _ this for mark _
 * @n: this is number
 * Return: void
 */
void print_line(int n)
{
	int i = 0;

	if (n <= 0)
	{
		_putchar('\n');
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			_putchar('_');

		}
		_putchar('\n');
	}
}
