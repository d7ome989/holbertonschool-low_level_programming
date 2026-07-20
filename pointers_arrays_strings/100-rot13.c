#include "main.h"
/**
 * rot13 - encodes a string using rot13
 * @str: the string to encode
 *
 * Return: a pointer to str
 */
char *rot13(char  *str)
{
	char old[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char new[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	int i;
	int j;

	for (i = 0 ; str[i] != '\0'; i++)
	{
		for (j = 0; old[j] != '\0'; j++)
			if (str[i] == old[j])
			{
				str[i] = new[j];
				break;
			}
	}
	return (str);

}
