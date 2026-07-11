#include "main.h"
/**
 * more_numbers - prints numbers from 1 to 14, ten times
 * Return: void
 */
void more_numbers(void)
{
	int i;
	int r;

	for (r = 0; r < 10; r++)
	{
		for (i = 1; i <= 14; i++)
		{
			if (i >= 10)
			{
				_putchar((i / 10) + '0');
			}
			_putchar((i % 10) + '0');
		}
		_putchar('\n');
	}
}
