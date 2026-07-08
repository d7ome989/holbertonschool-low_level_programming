#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: Prints the last digit of a randomly generated number
 * and checks its value.
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char a;
	char c;

	for (a = 'a'; a <= 'z'; a++)
	{
		putchar(a);
	}
	for (c = 'A'; c <= 'Z'; c++)
	{
		putchar(c);
	}
	putchar('\n');
	return (0);
}
