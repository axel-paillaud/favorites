#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//prototype
char get_input();
bool check_input();

// global variable
// 2100 car longueur max d'hyperlien IE est de 2083 caractères
char input[2100];
char mexit[4] = "exit";

int main(void)
{
	do
	{
	get_input();
	}
	while (check_input() != true);
}

char get_input()
{
	printf("Pass the link: \n");
	scanf("%2099s", input);
}

bool check_input()
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
