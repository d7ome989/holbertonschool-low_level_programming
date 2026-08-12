#include "lists.h"

/**
 * insert_dnodeint_at_index - inserts a new node at a given position
 * @h: pointer to a pointer to the head of the list
 * @idx: index where the new node should be added, starting at 0
 * @n: value to store in the new node
 *
 * Return: address of the new node, or NULL if it failed
 */
dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *current;
	unsigned int len;
	dlistint_t *new_node;

	len = dlistint_len(*h);

	if (idx == 0)
	{
		return (add_dnodeint(h, n));
	}
	if (idx == len)
	{
		return (add_dnodeint_end(h, n));
	}
	if (idx > len)
	{
		return (NULL);
	}

	current = get_dnodeint_at_index(*h, idx - 1);

	new_node = malloc(sizeof(dlistint_t));
	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->n = n;
	new_node->next = current->next;
	new_node->prev = current;

	if (current->next != NULL)
	{
		(current->next)->prev = new_node;
	}

	current->next = new_node;

	return (new_node);
}
