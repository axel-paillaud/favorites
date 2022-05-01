#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INITIAL_LINE_LENGTH (2)
//Ici, le 2 ne vaut pas comme un paramètre mais bien comme une valeur (à vérifier)

//prototype
char * get_string(void);

int main(void)
{
	char * string;

	printf("Veuillez écrire une phrase: \n");

	string = get_string();

	printf("La phrase que vous venez d'écrire est: \n%s\n", string);

	free(string);

	return 0;
}

char * get_string(void)
{
	char * string;
	int size;
	int length;
	int c;

	size = INITIAL_LINE_LENGTH;
	string = malloc(size);
	assert(string);

	length = 0;

	while((c = getchar()) != EOF && c != '\n')
	{
		if (length >= size-1)
			//Need more space !
		{
			size *= 2;

			//make length equal to new size
			//copy content if necessary 
			string = realloc(string, size);
		}

		string[length++] = c;
	}
	
	string[length] = '\0';

	return string;
}
