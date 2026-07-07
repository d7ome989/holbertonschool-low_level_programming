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
	int n;
	int last_d;

	srand(time(0));
	n = rand() - RAND_MAX / 2;

	last_d = n % 10;

	printf("Last digit of %d is %d ", n, last_d);

	if (last_d > 5)
	{
		printf("and is greater than 5\n");
	}
	else if (last_d == 0)
	{
		printf("and is 0\n");
	}
	else
	{
		printf("and is less than 6 and not 0\n");
	}

	return (0);
}
