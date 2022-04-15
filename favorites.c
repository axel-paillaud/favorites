#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//prototype
char get_input();
bool check_exit();
int check_input();
char* get_link();

// global variable
// 2100 car longueur max d'hyperlien IE est de 2083 caractères
char input[15];
char mexit[5] = "exit";
char mlink[5] = "link";
char mnote[5] = "note";
char mkey[4] = "key";

int main(void)
{
	do
	{
		// Ici, ouvrir le fichier favorites.csv. S'il n'existe pas, le créer
		// Penser à fclose le fichier à la fin
		FILE *file = fopen("favorites.csv", "a");
		if (file == NULL)
			return 1;


		// Obtenir l'input de l'user entre link, key, note
		get_input();
		int val_input = check_input();

		if (val_input == 1)
		{
			//Ajouter l'input à un fichier csv
			char *var_link = get_link();

			fprintf(file, "%s;\n", var_link);

			fclose(file);

			free(var_link);
		}
		else if (val_input == 2)
		{
			printf("note");	
		}
		else if (val_input == 3)
		{
			printf("key");	
		}
		else if (val_input == 4)
		{
			printf("\n");
			printf("Type of datas: link, note, key or enter 'exit' to quit the program.\n");	
			printf("\n");
		}
	}
	while (check_exit() != true);
	// pensez à vider la mémoire avec free ici si malloc a été utilisé pour table de hash
}

char get_input()
{
	printf("What is the type of data you want to store ?\n");
	scanf("%14s", input);
}

bool check_exit()
{
	char *n = input;
	int j = strlen(n) + 1;
	char arr[j];
	for (int i = 0; i <= j; i++)
	{
		arr[i] = n[i];
	}
	int result = strcmp(arr, mexit);
	if (result == 0 )
	{
		return true;
	}
}

int check_input()
{
	char *n = input;
	int j = strlen(n) + 1;
	char arr[j];
	
	strcpy(arr, n);

	int resultlink = strcmp(arr, mlink);
	int resultnote = strcmp(arr, mnote);
	int resultkey = strcmp(arr, mkey);
	int resultexit = strcmp(arr, mexit);

	if (resultlink == 0)
		return 1;
	else if (resultnote == 0)
		return 2;
	else if (resultkey == 0)
		return 3;
	else if (resultexit != 0)
		return 4;
	else
		return 0;
}

char* get_link()
{
	char tmp[2100];
	printf("Please past or write your hyperlink: \n");
	scanf("%s", tmp);

	int len = strlen(tmp) + 1;

	if (len > 2100)
	{
		printf("Fail: a link cannot be more than 2100 char.\n");
		exit(1);
		// Ok arrête bien la fonction, par contre quitte carrément le programme, voir si boucle do while mieux
	}

	char *var_link = malloc(sizeof(len));

	strcpy(var_link, tmp);

	return var_link;
}
