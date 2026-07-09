#include "main.h"

/**
 * print_last_digit - Prints the last digit of a number
 * @n: The number to check
 *
 * Return: The value of the last digit
 */
int print_last_digit(int n)
{
	int last;

	last = n % 10;

	if (last < 0)
	{
		_putchar(-last + '0');
		return (last);
	}

	_putchar(last + '0');
	return (last);
}
