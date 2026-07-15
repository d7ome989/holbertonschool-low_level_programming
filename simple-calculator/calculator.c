#include <stdio.h>

int main()
{
	int n;

	printf("Welcome to my calculater\n");
	printf("%s\n","1) Add");
	printf("%s\n", "2) Subtarct");
	printf("%s\n",  "3) Multiply");
	printf("%s\n", "4) Divide");
	printf("%s\n", "0) Quit");
	scanf("%d", &n);
	if(n == 0)
	{
		printf("bye!\n");
	}
	else
	{
		printf("Invalid choice");
	}
	return 0;

}
