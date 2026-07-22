#include "main.h"

/**
 * str_concat - concatenates two strings into a newly allocated string
 * @s1: the first string (treated as empty if NULL)
 * @s2: the second string (treated as empty if NULL)
 *
 * Return: a pointer to the newly allocated string containing s1
 *         followed by s2, or NULL if memory allocation fails
 */
char *str_concat(char *s1, char *s2)
{
	int size_1 = 0;
	int size_2 = 0;
	char *array;
	int i;
	int j;

	while (s1 != NULL && s1[size_1] != '\0')
		size_1++;
	while (s2 != NULL && s2[size_2] != '\0')
		size_2++;
	array = malloc((size_1 + size_2 + 1) * sizeof(*array));
	if (array == NULL)
		return (NULL);
	for (i = 0, j = 0; i < size_1; i++, j++)
		array[j] = s1[i];
	for (i = 0; i < size_2; i++, j++)
		array[j] = s2[i];
	array[j] = '\0';
	return (array);
}
