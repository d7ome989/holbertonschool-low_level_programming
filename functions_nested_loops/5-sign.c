#include "main.h"

/**
 * _isalpha - Checks for alphabetic character
 * @c: The character to check
 *
 * Return: 1 if c is a letter (lowercase or uppercase), 0 otherwise
 */
int print_sign(int n)
{
	if (n > 0)
        {
		_putchar('+');
        	return (1);
        }
        else if (n == 0)
        {
		_putchar('0');
        	return (0);
        }
        else
        {

        	return(-1);
        }
}
