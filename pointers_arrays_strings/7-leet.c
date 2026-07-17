#include "main.h"

/**
 * leet - encodes a string into 1337
 * @str: the string to encode
 *
 * Return: a pointer to str
 */
char *leet(char *str)
{
	char old[] = {'a', 'A', 'e', 'E', 'o', 'O', 't', 'T', 'l', 'L'};
	char new[] = {'4', '4', '3', '3', '0', '0', '7', '7', '1', '1'};
	int i;
	int j;

	for (i = 0; str[i] != '\0'; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (str[i] == old[j])
				str[i] = new[j];
		}
	}
	return (str);
}
