#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int *tmp;
	int nbr = 50;
	int *nbr_malloc = malloc(nbr * sizeof(int));

	*nbr_malloc = nbr;

	tmp = nbr_malloc;

	free(tmp);

	printf("%i\n", *tmp);
	printf("%i\n", *nbr_malloc);
}
