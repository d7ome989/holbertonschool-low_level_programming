#include "lists.h"

/**
 * free_dlistint - frees a dlistint_t list
 * @head: pointer to the head of the list to free
 *
 * Return: void
 */
void free_dlistint(dlistint_t *head)
{
	dlistint_t *current;
	dlistint_t *temp;

	for (current = head; current != NULL; current = temp)
	{
		temp = current->next;
		free(current);
	}
}
