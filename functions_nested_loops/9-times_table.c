#include "main.h"

/**
 * times_table - Prints the 9 times table, starting with 0
 *
 * Return: void
 */
void times_table(void)
{
	int hou;
	int mun;
	int result;

	for (hou = 0; hou <= 9; hou++)
	{
		for (mun = 0; mun <= 9; mun++)
		{
			result = hou * mun;

			if (result >= 10)
			{
				_putchar(result / 10 + '0');
			}
			_putchar(result % 10 + '0');

			if (mun == 9)
			{
				_putchar('\n');
			}
			else
			{
				_putchar(',');
				_putchar(' ');
			}
		}
	}
}
