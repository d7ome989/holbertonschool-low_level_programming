
#include "main.h"

/**
 * swap_int - swap number like a b change to b a
 * @a: this is a frist number
 * @b: this is a second number
 *
 * Return: void
 *
 *
 */
void swap_int (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b  = temp;

}
