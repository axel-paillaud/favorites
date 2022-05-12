#include <stdio.h>

void modifie_array(int arr[]);

int main(void)
{
	int arr[];

	modifie_array(arr);

	for(int i = 0; i < 4; i++)
	{
		printf("%i\n", arr[i]);
	}
}

void modifie_array(int arr[])
{
	arr[4];
	arr[0] = 10;
	arr[1] = 2;
	arr[2] = 56;
	arr[3] = 18;
}
