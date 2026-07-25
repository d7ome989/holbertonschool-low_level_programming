#include <stdio.h>
#include <stdlib.h>
#include "dog.h"

/**
 * new_dog - Creates a new dog structure.
 * @name: The name of the dog.
 * @age: The age of the dog.
 * @owner: The owner of the dog.
 * Return: Pointer to the new dog structure, or NULL on failure.
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *new_dog_ptr;
	char *new_name;
	char *new_owner;
	int i, name_len, owner_len;

	if (name == NULL || owner == NULL)
		return (NULL);

	new_dog_ptr = malloc(sizeof(dog_t));
	if (new_dog_ptr == NULL)
		return (NULL);

	for (name_len = 0; name[name_len] != '\0'; name_len++)
		;
	for (owner_len = 0; owner[owner_len] != '\0'; owner_len++)
		;

	new_name = malloc(sizeof(char) * (name_len + 1));
	new_owner = malloc(sizeof(char) * (owner_len + 1));
	if (new_name == NULL || new_owner == NULL)
	{
		free(new_name);
		free(new_owner);
		free(new_dog_ptr);
		return (NULL);
	}

	for (i = 0; i <= name_len; i++)
		new_name[i] = name[i];
	for (i = 0; i <= owner_len; i++)
		new_owner[i] = owner[i];

	new_dog_ptr->name = new_name;
	new_dog_ptr->age = age;
	new_dog_ptr->owner = new_owner;

	return (new_dog_ptr);
}
