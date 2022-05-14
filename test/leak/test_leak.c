#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *string;
    char arr_string[10] = "azertyuiop";

    string = malloc(10 * sizeof(char));

    strcpy(string, arr_string);

    string[5] = '\0';

    free(string);
}