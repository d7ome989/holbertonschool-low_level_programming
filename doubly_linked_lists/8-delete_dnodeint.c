#include <stdlib.h>
#include "lists.h"

/**
 * delete_at_beginning - deletes the head node of a dlistint_t list
 * @head: pointer to the pointer to the head of the list
 *
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_at_beginning(dlistint_t **head)
{
	dlistint_t *temp;

	if (*head == NULL)
	{
		return (-1);
	}

	temp = *head;
	*head = temp->next;
	if (*head != NULL)
	{
		(*head)->prev = NULL;
	}
	free(temp);

	return (1);
}

/**
 * delete_dnodeint_at_index - deletes the node at index of a dlistint_t list
 * @head: pointer to the pointer to the head of the list
 * @index: index of the node to delete, starting at 0
 *
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	dlistint_t *temp;
	unsigned int i;

	if (*head == NULL)
	{
		return (-1);
	}

	if (index == 0)
	{
		return (delete_at_beginning(head));
	}

	for (temp = *head, i = 0; temp != NULL && i < index; temp = temp->next, i++)
	{
	}

	if (temp == NULL)
	{
		return (-1);
	}

	if (temp->prev != NULL)
	{
		temp->prev->next = temp->next;
	}
	if (temp->next != NULL)
	{
		temp->next->prev = temp->prev;
	}

	free(temp);

	return (1);
}
