#include <stdio.h>

int main()
{

	printf("Welcome to my calculater\n");
	printf("%s\n","1) Add");
	printf("%s\n", "2) Subtarct");
	printf("%s\n",  "3) Multiply");
	printf("%s\n", "4) Divide");
	printf("%s\n", "0) Quit");
	int n;
	scanf("%d", &n);
	if(n == 0)
	{
		printf("bye!\n");
	}
	return 0;

}
