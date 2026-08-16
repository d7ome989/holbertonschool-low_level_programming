#include <stdlib.h>
#include <string.h>
#include "store.h"

/**
 * store_init - initialize an empty store
 * @st: store to initialize
 */
void store_init(store_t *st)
{
	if (st)
		st->head = NULL;
}

/**
 * store_add - insert a session into the store, taking ownership of it
 * @st: store to insert into
 * @s: session to insert (ownership is always taken: stored on success,
 * destroyed on any failure path so the caller never has to free it)
 *
 * Return: 1 on success, 0 on failure (invalid arguments, duplicate id,
 * or allocation failure)
 */
int store_add(store_t *st, session_t *s)
{
	node_t *n, *cur;

	if (!st || !s || !s->id)
	{
		session_destroy(s);
		return (0);
	}

	cur = st->head;
	while (cur)
	{
		if (cur->sess && cur->sess->id && strcmp(cur->sess->id, s->id) == 0)
		{
			session_destroy(s);
			return (0);
		}
		cur = cur->next;
	}

	n = (node_t *)malloc(sizeof(*n));
	if (!n)
	{
		session_destroy(s);
		return (0);
	}

	n->sess = s;
	n->next = st->head;
	st->head = n;
	return (1);
}

/**
 * store_get - look up a session by id
 * @st: store to search
 * @id: id to search for
 *
 * Return: pointer to the matching session, or NULL if not found
 */
session_t *store_get(store_t *st, const char *id)
{
	node_t *cur;

	if (!st || !id)
		return (NULL);

	cur = st->head;
	while (cur)
	{
		if (cur->sess && cur->sess->id && strcmp(cur->sess->id, id) == 0)
			return (cur->sess);
		cur = cur->next;
	}
	return (NULL);
}

/**
 * store_delete - remove a session from the store by id
 * @st: store to remove from
 * @id: id to remove
 * @out: if non-NULL, ownership of the removed session is transferred to
 * the caller through *out and the session is NOT destroyed here; if
 * NULL, the session is destroyed immediately (delete-and-destroy)
 *
 * Return: 1 if a session was removed, 0 if not found
 */
int store_delete(store_t *st, const char *id, session_t **out)
{
	node_t *cur, *prev;

	if (!st || !id)
		return (0);

	prev = NULL;
	cur = st->head;

	while (cur)
	{
		if (cur->sess && cur->sess->id && strcmp(cur->sess->id, id) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				st->head = cur->next;

			if (out)
				*out = cur->sess;
			else
				session_destroy(cur->sess);

			free(cur);
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}

	return (0);
}

/**
 * store_destroy - free every session and node in the store
 * @st: store to destroy (safe to call with NULL, on an already-empty
 * store, or repeatedly - the store is left empty and reusable)
 */
void store_destroy(store_t *st)
{
	node_t *cur, *next;

	if (!st)
		return;

	cur = st->head;
	while (cur)
	{
		next = cur->next;
		session_destroy(cur->sess);
		free(cur);
		cur = next;
	}
	st->head = NULL;
}
