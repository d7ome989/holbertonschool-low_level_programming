#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main()
{
	int n;
	int excess;
	int add;
	int i;
	char password[35];

	srand(time(NULL));

	n = 25;
	excess = 2772 - (97 * n);

	for (i = 0; i < n; i++)
	{
		if (excess > 25)
			add = 25;
		else if (excess > 0)
			add = excess;
		else
			add = 0;
		password[i] = 'a' + add;
		excess = excess - add;
	}
	password[n] = '\0';

	printf("%s\n", password);
	return (0);
}
