#include <stdio.h>

char *get_link();

int main(void)
{
	printf("%s\n", get_link());
}

char* get_link()
{
	return "Hello world\n";
}
