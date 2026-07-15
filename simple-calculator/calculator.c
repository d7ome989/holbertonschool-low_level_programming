#include <stdio.h>

int main()
{
	int n;
	int a;
	int b;
	int result;

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
	else if (n == 1)
	{
		printf("ok pless enter Frist number .\n");
		scanf("%d", &a);
		printf("ok pless enter second number .\n");
                scanf("%d", &b);
		result = a + b;
                printf("result is %d\n ", result);

	}
	else if (n == 2)
        {
                printf("ok pless enter Frist number .\n");
                scanf("%d", &a);
                printf("ok pless enter second number .\n");
                scanf("%d", &b);
                result = a - b;
                printf("result is %d\n ", result);

        }
	else if (n == 3)
        {
                printf("ok pless enter Frist number .\n");
                scanf("%d", &a);
                printf("ok pless enter second number .\n");
                scanf("%d", &b);
                result = a * b;
                printf("result is %d\n ", result);

        }
	else if (n == 4)
        {
                printf("ok pless enter Frist number .\n");
                scanf("%d", &a);
                printf("ok pless enter second number .\n");
                scanf("%d", &b);
                result = a / b;
                printf("result is %d\n ", result);
        }
	else
	{
		printf("Invalid choice");
	}
	return 0;

}
