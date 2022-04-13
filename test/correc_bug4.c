#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//prototype
char get_input();
bool check_exit();
int check_input();

// global variable
// 2100 car longueur max d'hyperlien IE est de 2083 caractères
char input[15];
char get_link[2100];
char mexit[5] = "exit";
char mlink[5] = "link";
char mnote[5] = "note";
char mkey[4] = "key";

int main(void)
{
	do
	{
	get_input();
	check_input();
	}
	while (check_exit() != true);
}

char get_input()
{
	printf("What is the type of data you want to store ?\n");
	scanf("%14s", input);
}

bool check_exit()
{
	char *n = input;
	int j = strlen(n);
	char arr[j];
	for (int i = 0; i <= j; i++)
	{
		arr[i] = n[i];
	}
	int result = strcmp(arr, mexit);
	printf("%i\n", result);
	if (result == 0 )
	{
		printf("Vous venez de taper exit\n");
		return true;
	}
}

int check_input()
{
	char *n = input;
	int j = strlen(n);
	char arr[j];
	
	strcpy(arr, n);

	int resultlink = strcmp(arr, mlink);
	int resultnote = strcmp(arr, mnote);
	int resultkey = strcmp(arr, mkey);

	if (resultlink == 0)
	{
		printf("Vous venez de taper link\n");
		return 1;
	}
	else if (resultnote == 0)
	{
		printf("Vous venez de taper note\n");
		return 2;
	}
	else if (resultkey == 0)
	{
		printf("Vous venez de taper key\n");
		return 3;
	}
	else
		return 0;
}
