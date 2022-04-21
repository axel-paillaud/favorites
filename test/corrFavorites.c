#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

//prototype
char get_input();
bool check_exit();
int check_input();
char* get_link();
char * get_tag();
int add_comment(FILE *file);

// global variable
char input[15];
char mlink[5] = "link";
char mnote[5] = "note";
char mkey[4] = "key";
char mexit[5] = "exit";
char mstop[5] = "stop";

int cmp = 1;

int main(void)
{
	do
	{
		// Ici, ouvrir le fichier favorites.csv. S'il n'existe pas, le créer
		// Penser à fclose le fichier à la fin
		FILE *file = fopen(".link", "a");
		if (file == NULL)
			return 1;


		// Obtenir l'input de l'user entre link, key, note
		get_input();
		int val_input = check_input();

		if (val_input == 1)
		{
			//Ajouter l'input à un fichier csv
			char *var_link = get_link();

			fprintf(file, "%s|END|", var_link);
		
			printf("Please enter tags one by one, enter 'stop' when you finish: \n");

			do
			{
				char * var_tag = get_tag();
				cmp = strcmp(var_tag, mstop);

				if (cmp != 0)
					fprintf(file, "<%s>", var_tag);

				free(var_tag);

			}
			while (cmp != 0);
			
			fprintf(file, "|END|");

			add_comment(file);
			
			fclose(file);

			free(var_link);

			exit(0);
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
		return true;
	else
		return false;
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

	char *var_link = malloc(sizeof(char) * len);

	strcpy(var_link, tmp);

	return var_link;
}

char * get_tag()
{
	char tmp[51];
	bool check_len = false;
	bool check_alpha = false;

	//check si le tag ne contient pas de numéro ou de symbole, uniquement des lettres. Convertir les majuscules en minuscules également.
	do
	{
		check_alpha = true;

		scanf("%s", tmp);

		int len = strlen(tmp);

		if (len <= 50)
			check_len = true;
		else
			printf("Fail: the maximum lenght of a tag is 50 char.\n");

		for (int i = 0; i < len; i++)
		{
			if (!(isalpha(tmp[i])))
				check_alpha = false;
			
			if (isupper(tmp[i]))
				tmp[i] = tolower(tmp[i]);
		}
		if (check_alpha == false)
			printf("Fail: Your tag must have only letters.\n");
	}
	while (check_alpha != true || check_len != true);
	
	int len = strlen(tmp);

	char * var_tag = malloc(sizeof(len));

	strcpy(var_tag, tmp);

	return var_tag;
}

int add_comment(FILE *file)
{
	char comment[3000];
	char answer_comment[4]; 
	char yes[4] = "yes";
	char no[3] = "no";
	char y[2] ="y";
	char n[2] = "n";

	printf("Do you want to add a comment ? (y/n)\n");
	fgets(answer_comment, 4, stdin);

	printf("%i\n", errno);
	puts(strerror(errno));

	int cmpYes = strcmp(answer_comment, yes);
	int cmpY = strcmp(answer_comment, y);
	int cmpNo = strcmp(answer_comment, no);
	int cmpN = strcmp(answer_comment, n);

	printf("%i\n", cmpYes);

	if (cmpYes == 0||cmpY == 0)
	{
		printf("Please enter your comment:\n");
		fgets(comment, 3000, stdin);
		fprintf(file, "%s|END|", comment);
	}
	else if (cmpNo == 0||cmpN == 0)
	{
	       printf("Vous venez de choisir non\n");
	}
	else
		printf("Choix invalide\n");	
}
