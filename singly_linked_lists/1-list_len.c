#include "lists.h"

/**
 * list_len - returns the number of elements in a linked list_t list
 * @h: pointer to the head of the list
 *
 * Return: the number of elements
 */
size_t list_len(const list_t *h)
{
	size_t count;

	for (count = 0; h != NULL; h = h->next, count++)
		;

	return (count);
}
