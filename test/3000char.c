#include <stdio.h>

int main(void)
{
	FILE *file = fopen("3000char.txt", "a");

	char var_char = 'a';

	for (int i = 0; i < 3000; i++)
	{
		fprintf(file, "%c", var_char);
	}

	fclose(file);
}
