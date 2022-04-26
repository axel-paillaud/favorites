#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//prototype
void get_input();
bool check_exit();
int check_input();
char* get_link();
char * get_tag();
int list_tag(FILE * file);
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
			//Ajouter l'input à un fichier caché .link 
			char *var_link = get_link();

			fprintf(file, "%s|END|", var_link);
		
			printf("Please enter tags one by one, enter 'stop' when you finish: \n");

			list_tag(file);

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
		else if (val_input == -1)
		{
			printf("\n");
			printf("Type of datas: link, note, key or enter 'exit' to quit the program.\n");	
			printf("\n");
		}
	}
	while (check_exit() != true);
	// pensez à vider la mémoire avec free ici si malloc a été utilisé pour table de hash
}

void get_input()
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
		return -1;
	else
		return -2;
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
	//TODO Il faudra soit check avec scanf si l'utilisateur à taper des espaces, soit check en utilisant fgets
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
	
	int len = (strlen(tmp) + 1);

	char * var_tag = malloc(sizeof(len));

	strcpy(var_tag, tmp);

	return var_tag;
}

int list_tag(FILE * file)
{
	char mstop[5] = "stop";
	int i = 0;
	int cmp_stop = 1;

	char * list_tag[30];

	do
	{
		int cmp_same_word = 1;
		char * var_tag = get_tag();
		bool check_tag_exist = false;

		cmp_stop = strcmp(var_tag, mstop);

		list_tag[i] = var_tag;

		if (i > 30)
		{
			printf("You can't have more than 30 tags.\n");
			return 1;
		}

		// Check if the tag was already type by the user. If not, add the tag to the file.
		for (int j = 0; j < i; j++)
		{
			cmp_same_word = strcmp(list_tag[i], list_tag[j]);
			if (cmp_same_word == 0)
			{
				printf("You already enter this tag.\n");
				check_tag_exist = true;
			}
		}

		if (check_tag_exist != true && cmp_stop != 0)
		{
			fprintf(file, "<%s>", list_tag[i]);
		}

		i++;
	}
	while (cmp_stop != 0);

	for (int j = 0; j < i; j++)
		free(list_tag[j]);

	fprintf(file, "|END|");
	return 0;
}

int add_comment(FILE *file)
{
	char comment[3000];
	char answer_comment[20];
	char yes[4] = "yes";
	char no[3] = "no";
	char y[2] = "y";
	char n[2] = "n";
	bool check_comment = false;
	while ((getchar()) != '\n');

	printf("Do you want to add a comment ? (y/n)\n");
	do
	{
		fgets(answer_comment, 20, stdin);

		int answ_len = strlen(answer_comment);
		answer_comment[answ_len - 1] = 0;
		int cmpYes = strcmp(answer_comment, yes);
		int cmpY = strcmp(answer_comment, y);
		int cmpNo = strcmp(answer_comment, no);
		int cmpN = strcmp(answer_comment, n);
		int cmpExit = strcmp(answer_comment, mexit);

		if (answ_len > 18)
		{
			printf("Too much character\n");
			// clear input stream
			while ((getchar()) != '\n');

			check_comment = false;
		}
		else if (cmpYes == 0||cmpY == 0)
		{
			printf("Please enter your comment:\n");
	
			while ((getchar()) != '\n');
			fgets(comment, 3000, stdin);
			//Ici, supprimer le dernier caractère de retour à la ligne de fgets
			int len = strlen(comment);
			comment[len - 1] = 0;
	
			fprintf(file, "'%s'", comment);
			fprintf(file, "|END|\n");
			check_comment = true;
			return 0;
		}
		else if (cmpNo == 0||cmpN == 0)
		{
			check_comment = true;
		       return 0;
		}
		else if (cmpExit == 0)
		{
			check_comment = true;
			return 0;
		}
		else
		{
			printf("Invalid choice\n");	
			check_comment = false;
		}
	}
	while (check_comment != true);
	return 1;
}

