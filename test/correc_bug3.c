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
char mexit[4] = "exit";
char coco[4] = "link";
char papa[4] = "note";

int main(void)
{
	do
	{
	printf("%s\n", mexit);
	printf("%s\n", coco);
	printf("%s\n", papa);
	get_input();
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

