#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
		get_input();
		int val_input = check_input();

		if (val_input == 1)
		{
			char *var_link = get_link();
			printf("%s\n", var_link);
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
	char tmp_link[2100];
	printf("Please past or write your hyperlink: \n");
	scanf("%2099s", tmp_link);

	int len = strlen(tmp_link) + 1;

	if (len > 2100)
	{
		printf("Fail: a link cannot be more than 2100 char.\n");
	}

	char *var_link[len];
	strcpy(*var_link, tmp_link);
	return var_link;
}
