#include <stdio.h>

//prototype
char get_link();

int main(void)
{
	char *link;
	link = get_link();
	printf("%s\n", link);
}

char get_link()
{
	char *link;
	printf("Pass the link: \n");
	scanf("%s", link);
	return link;
}
