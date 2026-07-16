#include "main.h"

/**
 * _strncat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source string
 * @n: that is a number of carcter to print
 * Return: a pointer to dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	for (j = 0; src[j] != src[n]; j++, i++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}
