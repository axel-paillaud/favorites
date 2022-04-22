#include <stdio.h>

int main(void)
{
	char str[20];

	fgets(str, 20, stdin);

	printf("%s\n", str);
}
