#include "main.h"

/**
 * _strdup - creates a duplicate of a given string
 * @str: the string to duplicate
 *
 * Return: a pointer to the duplicated string, or NULL if str
 *         is NULL or if memory allocation fails
 */
char *_strdup(char *str)
{
	int size;
	char *array;
	int i;

	if (str == NULL)
	{
		return (NULL);
	}
	for (size = 0; str[size] != '\0'; size++)
	{
	}
	size += 1;
	array = malloc(size * sizeof(*array));
	if (array == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < size - 1; i++)
	{
		array[i] = str[i];
	}
	array[i] = '\0';
	return (array);
}
