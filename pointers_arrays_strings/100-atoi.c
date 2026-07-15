#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: The string to convert
 *
 * Description: Skips leading characters, counts minus signs to determine
 * the sign, then reads the first sequence of digits and builds the number.
 *
 * Return: The integer value, or 0 if there are no digits
 */
int _atoi(char *s)
{
	int i;
	int sign;
	int number;
	int started;

	sign = 1;
	number = 0;
	started = 0;

	for (i = 0; s[i] != '\0' && started == 0; i++)
	{
		if (s[i] == '-')
			sign = sign * -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			started = 1;
			for (; s[i] >= '0' && s[i] <= '9'; i++)
			{
				number = number * 10 + (s[i] - '0') * sign;
			}
			i--;
		}
	}
	return (number);
}
