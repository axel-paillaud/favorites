#include <stdio.h>
#include <string.h>

int main(void)
{
	char * list_tag[30];

	char * var_tag1 = "tag1";
	char * var_tag2 = "tag2";
	char * var_tag3 = "tag3";
	char * var_tag4 = "tag4";

	list_tag[0] = var_tag1;
	list_tag[1] = var_tag2;
	list_tag[2] = var_tag3;
	list_tag[3] = var_tag4;

	printf("Valeurs de l'index 0 de la list_tag: ");
	printf("%s\n", list_tag[0]);

	printf("Valeurs de l'index 1 de la list_tag: ");
	printf("%s\n", list_tag[1]);
}
