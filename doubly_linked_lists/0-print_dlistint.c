#include "lists.h"
/**
 * print_dlistint - prints all elements of a dlistint_t list
 * @h: pointer to the head of the list
 *
 * Return: number of nodes in the list
 */
size_t print_dlistint(const dlistint_t *h)
{
	size_t count = 0;
	const dlistint_t *current = h;

	for (count = 0; current != NULL; count++)
	{
		printf("%d\n", current->n);
		current = current->next;
	}

	return (count);
}
