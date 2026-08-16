#include "main.h"

/**
 * str_length - computes the length of a string, recursively
 * @s: the string
 *
 * Return: the length of s
 */
int str_length(char *s)
{
	if (*s == '\0')
		return (0);

	return (1 + str_length(s + 1));
}

/**
 * is_palindrome_helper - checks if s is a palindrome between i and j
 * @s: the string
 * @i: index from the start
 * @j: index from the end
 *
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome_helper(char *s, int i, int j)
{
	if (i >= j)
		return (1);

	if (s[i] != s[j])
		return (0);

	return (is_palindrome_helper(s, i + 1, j - 1));
}

/**
 * is_palindrome - checks if a string is a palindrome
 * @s: the string
 *
 * Return: 1 if palindrome, 0 otherwise
 */
int is_palindrome(char *s)
{
	int len;

	len = str_length(s);

	return (is_palindrome_helper(s, 0, len - 1));
}
