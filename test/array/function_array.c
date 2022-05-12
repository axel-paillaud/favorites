#include <stdio.h>

void modifie_array(int arr[]);

int main(void)
{
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for(int i = 0; i < 10; i++)
	{
		printf("%i\n", arr[i]);
	}

	modifie_array(arr);

	for(int i = 0; i < 10; i++)
	{
		printf("%i\n", arr[i]);
	}
}

void modifie_array(int arr[])
{
	arr[4] = 18;
	arr[2] = 44;
	arr[8] = 89;
}
