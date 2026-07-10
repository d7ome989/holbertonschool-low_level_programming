#include "main.h"

/**
 * jack_bauer - Prints every minute of the day, from 00:00 to 23:59
 *
 * Return: void
 */
void jack_bauer(void)
{
	int hou;
	int mun;

	for (hou = 0; hou <= 23; hou++)
	{
		for (mun = 0; mun <= 59; mun++)
		{
			_putchar(hou / 10 + '0');
			_putchar(hou % 10 + '0');
			_putchar(':');
			_putchar(mun / 10 + '0');
			_putchar(mun % 10 + '0');
			_putchar('\n');
		}
	}
}
