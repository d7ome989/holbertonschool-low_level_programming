#include <stdlib.h>
#include <string.h>
#include "session.h"

/**
 * dup_string - allocate a heap copy of a NUL-terminated string
 * @str: string to copy (may be NULL)
 *
 * Return: pointer to the new copy, or NULL if str is NULL or
 * allocation fails
 */
static char *dup_string(const char *str)
{
	char *copy;
	size_t len;

	if (!str)
		return (NULL);

	len = strlen(str) + 1;
	copy = (char *)malloc(len);
	if (!copy)
		return (NULL);

	memcpy(copy, str, len);
	return (copy);
}

/**
 * dup_data - allocate a heap copy of a raw byte buffer
 * @data: buffer to copy
 * @data_len: number of bytes to copy
 *
 * Return: pointer to the new copy, or NULL on allocation failure
 */
static unsigned char *dup_data(const unsigned char *data, size_t data_len)
{
	unsigned char *copy;

	copy = (unsigned char *)malloc(data_len);
	if (!copy)
		return (NULL);

	memcpy(copy, data, data_len);
	return (copy);
}

/**
 * session_create - allocate and initialize a new session, deep-copying
 * the id string and the data buffer so the session owns independent
 * heap memory that does not depend on the caller's buffers staying valid
 * @id: session identifier string (copied, may be NULL)
 * @uid: user id associated with the session
 * @data: data buffer to copy into the session (may be NULL if data_len is 0)
 * @data_len: number of bytes to copy from data
 *
 * Return: pointer to the new session, or NULL on allocation failure
 */
session_t *session_create(const char *id, unsigned int uid,
	const unsigned char *data, size_t data_len)
{
	session_t *s;

	s = (session_t *)malloc(sizeof(*s));
	if (!s)
		return (NULL);

	s->id = dup_string(id);
	if (id && !s->id)
	{
		free(s);
		return (NULL);
	}

	s->uid = uid;
	s->data = NULL;
	s->data_len = 0;

	if (data_len > 0)
	{
		s->data = dup_data(data, data_len);
		if (!s->data)
		{
			free(s->id);
			free(s);
			return (NULL);
		}
		s->data_len = data_len;
	}

	return (s);
}

/**
 * session_set_data - replace a session's data buffer, resizing it safely
 * @s: session to update
 * @data: new data to copy in (may be NULL if data_len is 0)
 * @data_len: length of the new data; 0 clears the buffer
 *
 * Return: 1 on success, 0 on failure (session left unchanged on failure)
 */
int session_set_data(session_t *s, const unsigned char *data, size_t data_len)
{
	unsigned char *tmp;

	if (!s)
		return (0);

	if (data_len == 0)
	{
		free(s->data);
		s->data = NULL;
		s->data_len = 0;
		return (1);
	}

	tmp = (unsigned char *)realloc(s->data, data_len);
	if (!tmp)
		return (0);

	s->data = tmp;
	memcpy(s->data, data, data_len);
	s->data_len = data_len;
	return (1);
}

/**
 * session_destroy - free a session and all memory it owns
 * @s: session to destroy (safe to call with NULL)
 */
void session_destroy(session_t *s)
{
	if (!s)
		return;

	free(s->id);
	free(s->data);
	free(s);
}
