#include <stdio.h>

int main(void)
{

	do
	{

	}
	while()
}

char * get_string(void)
{
        // Thanks to the computer scientist James Aspnes for this piece of code, this really help me out
        char * string;
        int size;
        int length;
        int c;

        size = INITIAL_STRING_LENGTH;
        string = malloc(size);

        if (string == NULL)
        {
                printf("Impossible to create string, memory out");
                exit(0);
        }

        length = 0;

        while((c = getchar()) != EOF && c != '\n')
        {
                if (length  >= size-1)
                {
                        //Need more space!
                        size *= 2;

                        string = realloc(string, size);
                }

                string[length++] = c;
        }

        string[length] = '\0';

        return string;
}
