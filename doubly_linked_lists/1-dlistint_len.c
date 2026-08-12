#include "lists.h"
/**
 * dlistint_len - returns number of a dlistint_t list
 * @h: pointer to the head of the list
 *
 * Return: number of nodes in the list
 */
size_t dlistint_len(const dlistint_t *h)
{
	size_t count = 0;
	const dlistint_t *current = h;
int n = 0;
	for (count = 0; current != NULL; count++)
	{
		current = current->next;
	}

	return (count);
}
