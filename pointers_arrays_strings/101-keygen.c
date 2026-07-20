#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int main()
{
	int sum;
	int r;
	char c;
	int remaining;

	srand(time(NULL));

	for (sum = 0; sum < 2772; )
	{
		remaining = 2772 - sum;

		if (remaining >= 'a' && remaining <= 'z')
		{
			c = remaining;
		}
		else if (remaining < 'a' + 'a')
		{
			c = 'a';
		}
		else
		{
			r = rand() % 26;
			c = r + 'a';
		}
		printf("%c", c);
		sum = sum + c;
	}
	printf("\n");
	return (0);
}

