#include <stdio.h>

int main(void)
{
	char str[20];

	FILE *file = fopen("file.txt", "a");

	if(file == NULL)
	{
		printf("Erreur\n");
		return(-1);
	}
	else
	{
		fgets(str, 20, stdin);

		fprintf(file, "%s", str);
	}

	fclose(file);
}
