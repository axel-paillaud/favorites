#include <stdio.h>

int myFunction(FILE *file);
char str[20];

int main(void)
{
	FILE *file = fopen("file.txt", "a");

	if(file == NULL)
	{
		printf("Erreur\n");
		return(-1);
	}
	else
	{
		myFunction(file);
	}

	fclose(file);
}

int myFunction(FILE *file)
{
	fgets(str, 20, stdin);

	fprintf(file, "%s", str);
}
