#include <stdio.h>

/**
 * main - prints the first argument passed to the program
 * @argc: the number of arguments
 * @argv: array of arguments
 *
 * Return: always 0
 */
int main(int argc, char *argv[])
{
	printf("%s\n", *argv);

	return (argc);
}
