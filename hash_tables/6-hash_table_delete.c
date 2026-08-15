#include "hash_tables.h"

/**
 * free_list - frees a linked list of hash nodes
 * @head: pointer to the head of the list
 *
 * Return: void
 */
void free_list(hash_node_t *head)
{
	hash_node_t *current;
	hash_node_t *temp;

	current = head;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
}

/**
 * hash_table_delete - deletes a hash table
 * @ht: the hash table to delete
 *
 * Return: void
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int i;

	if (ht == NULL)
	{
		return;
	}

	for (i = 0; i < ht->size; i++)
	{
		free_list(ht->array[i]);
	}

	free(ht->array);
	free(ht);
}
