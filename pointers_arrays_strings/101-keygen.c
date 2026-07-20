#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main()
{
	int n;
	int excess;
	int add;
	int i;
	char password[30];

	srand(time(NULL));

	/* عدد الأحرف بين 23 و 28، عشان يكون فيه حل صالح دايمًا */
	n = 23 + (rand() % 6);

	/* كل الأحرف تبدأ بـ 'a' (97)، والفرق نوزعه بعدين */
	excess = 2772 - (97 * n);

	for (i = 0; i < n; i++)
	{
		add = (excess < 25) ? excess : 25;
		password[i] = 'a' + add;
		excess = excess - add;
	}
	password[n] = '\0';

	printf("%s\n", password);
	return (0);
}
