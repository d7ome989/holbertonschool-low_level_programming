#include "lists.h"

/**
 * sum_dlistint - returns the sum of all data (n) in a dlistint_t list
 * @head: pointer to the head of the list
 *
 * Return: sum of all the n values, or 0 if the list is empty
 */
int sum_dlistint(dlistint_t *head)
{
	dlistint_t *current;
	int sum;

	current = head;
	for (sum = 0; current != NULL; current = current->next)
	{
		sum += current->n;
	}

	return (sum);
}
