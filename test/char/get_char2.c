#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_link();

int main(void)
{
	char *n = get_link();
	printf("%s\n", n);
	free(n);
}

char* get_link()
{
	char tmp[2100];

	scanf("%s", tmp);

	int i = strlen(tmp) + 1;
	char *arr = malloc(sizeof(i));
	
	strcpy(arr, tmp);

	return arr;
}
