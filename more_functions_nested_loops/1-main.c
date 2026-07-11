#include "main.h"
#include <stdio.h>

/**
 * main - tests _isupper function
 * Return: always 0
 */
int main(void)
{
	char c;

	for (c = 'A'; c <= 'z'; c++)
	{
		printf("%c: %d\n", c, _isupper(c));
	}

	return (0);
}
