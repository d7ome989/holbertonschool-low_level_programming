#include "main.h"

/**
 * is_prime_helper - checks if n is divisible by div or any number after it
 * @n: the number to check
 * @div: the current divisor being tested
 *
 * Return: 0 if n is divisible by div (not prime), 1 if prime
 */
int is_prime_helper(int n, int div)
{
	if (div * div > n)
		return (1);

	if (n % div == 0)
		return (0);

	return (is_prime_helper(n, div + 1));
}

/**
 * is_prime_number - checks if an integer is a prime number
 * @n: the number to check
 *
 * Return: 1 if n is prime, 0 otherwise
 */
int is_prime_number(int n)
{
	if (n < 2)
		return (0);

	return (is_prime_helper(n, 2));
}
