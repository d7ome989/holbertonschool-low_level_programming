#include "main.h"
#include <stdlib.h>

/**
* string_nconcat - concatenates two strings, using at most n bytes from s2
* @s1: first string
* @s2: second string
* @n: number of bytes to use from s2
*
* Return: pointer to the newly allocated concatenated string
*/
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	unsigned int len1 = 0, len2 = 0, i, j;

	char *ptr;

	for (i = 0; s1 && s1[i]; i++)
		len1++;
	for (i = 0; s2 && s2[i]; i++)
		len2++;
	if (n < len2)
		len2 = n;
	ptr = malloc((len1 + len2 + 1) * sizeof(*ptr));
	if (ptr == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len1; i++)
		ptr[i] = s1[i];
	for (j = 0; j < len2; j++)
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';

	return (ptr);
}
