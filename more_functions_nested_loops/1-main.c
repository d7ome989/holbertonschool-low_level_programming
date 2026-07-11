#include "main.h"
#include <stdio.h>

int main(void)
{
	char c;

	for (c = '/'; c <= ':'; c++)
	{
		printf("%c: %d\n", c, _isdigit(c));
	}

	return (0);
}
