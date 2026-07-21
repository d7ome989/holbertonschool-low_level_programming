#include "main.h"

/**
 * print_num - recursively prints the digits of a number
 * @n: the number to print
 *
 * Return: nothing
 */
void print_num(int n)
{
	int last_digit;

	last_digit = n % 10;
	if (last_digit < 0)
	{
		last_digit = last_digit * -1;
	}

	if (n <= -10 || n >= 10)
	{
		print_num(n / 10);
	}
	_putchar(last_digit + '0');
}

/**
 * print_number - prints an integer
 * @n: the integer to print
 *
 * Return: nothing
 */
void print_number(int n)
{
	if (n < 0)
	{
		_putchar('-');
	}
	print_num(n);
}
