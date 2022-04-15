#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * get_tag();

int main (void)
{
	char * string = get_tag();
	printf("%s\n", string);
}

char * get_tag()
{
	char tmp[1000];

	printf("Veuillez rentrer un tag: ");
	scanf("%s", tmp);

	int len = strlen(tmp);

	if (len > 1000)
	{
		printf("Longueur maximum du commentaire de 1000 caractère.\n");
		exit(0);
	}

	char * var_tag = malloc(sizeof(len));
	strcpy(var_tag, tmp);
	return var_tag;
}
