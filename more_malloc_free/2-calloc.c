#include "main.h"

/**
 * _calloc - allocates memory for an array and initializes it to zero
 * @nmemb: number of elements in the array
 * @size: size in bytes of each element
 *
 * Return: pointer to the allocated and zeroed memory, or NULL if
 *         nmemb or size is 0, or if malloc fails
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ptr;
	unsigned int i;
	char *p;

	if (nmemb == 0 || size == 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	p = ptr;
	for (i = 0; i < nmemb * size; i++)
		p[i] = 0;
	return (ptr);
}
