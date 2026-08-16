#include "main.h"

/**
 * sqrt_helper - helper function that tries values of x recursively
 * @n: the original number
 * @x: the current value being tested
 *
 * Return: the natural square root of n, or -1 if it doesn't exist
 */
int sqrt_helper(int n, int x)
{
	if (x * x == n)
		return (x);

	if (x * x > n)
		return (-1);

	return (sqrt_helper(n, x + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: the number
 *
 * Return: the natural square root of n, or -1 if it doesn't exist
 */
int _sqrt_recursion(int n)
{
	return (sqrt_helper(n, 0));
}
