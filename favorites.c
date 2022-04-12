#include <stdio.h>

//prototype
char get_input();

// global variable
// 2100 car longueur max d'hyperlien IE est de 2083 caractères
char input[2100];

int main(void)
{
	do
	{
	get_input();
	printf("%s\n", input);
	}
	while (input != "exit");
}

char get_input()
{
	printf("Pass the link: \n");
	scanf("%2099s", input);
}
