#include <stdio.h>

//prototype
char get_link();

// global variable
char link[50];

int main(void)
{
	get_link();
	printf("%s\n", link);
}

char get_link()
{
	printf("Pass the link: \n");
	scanf("%49s", link);
}
