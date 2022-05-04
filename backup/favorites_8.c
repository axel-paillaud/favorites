#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INITIAL_STRING_LENGTH (2)

//prototype
char * get_string(void);
bool search_or_add();
bool check_exit(char * var_fav);
void get_fav(FILE *file);
char * get_tag();
int list_tag(FILE * file);
int add_comment(FILE *file);

// global variable
char mexit[5] = "exit";
char mstop[5] = "stop";
char s[2] = "s";

int main(void)
{
	bool check_search_or_add = search_or_add();

	if (check_search_or_add == true)
	{
		FILE *file = fopen(".favorites.db", "r");
		if (file == NULL)
		{
			printf("Impossible to read the favorites files.\n");
			return 1;
		}

		printf("SEARCH TODO\n");

		fclose(file);
	}

	else
	{
		FILE *file = fopen(".favorites.db", "a");
		if (file == NULL)
		{
			printf("Impossible to open the favorites file.\n");
			return 1;
		}

		get_fav(file);

		list_tag(file);

		add_comment(file);
			
		fclose(file);

		exit(0);
	}
}

bool search_or_add()
{
	//true = search. change bool for int if need more than 2 input.
	bool check_correct_input = false;
	char * user_input; 

	char search[7] = "search";
	char s[2] = "s";
	char add[4] = "add";
	char a[2] = "a";

	printf("Do you want to add note, or search for an existing note ?\n");

	do
	{
		bool check_alpha = true;

		user_input = get_string();

		int input_len = strlen(user_input);

		if (input_len >= 10)
		{
			printf("Too much character. Write 'search' or 's', 'add' or 'a'.\n");
			free(user_input);
		}
		else
		{
			for (int i = 0; i < input_len; i++)
			{
				if (!(isalpha(user_input[i])))
					check_alpha = false;

				if (isupper(user_input[i]))
					user_input[i] = tolower(user_input[i]);
			}
			if (check_alpha == false)
			{
				printf("Only normal letters are allowed. Write 'search' or 's', 'add', or 'a'");
				free(user_input);
			}
			else
			{
				int cmpSearch = strcmp(user_input, search);
				int cmpS = strcmp(user_input, s);
				int cmpAdd = strcmp(user_input, add);
				int cmpA = strcmp(user_input, a);

				if (cmpSearch == 0||cmpS == 0)
				{
					check_correct_input = true;
					free(user_input);	
					return true;
				}
				else if (cmpAdd == 0||cmpA == 0)
				{
					check_correct_input = true;
					free(user_input);
					return false;
				}
				else
				{
					printf("Invalid input. Write 'search' or 's', 'add' or 'a'.\n");
					free(user_input);
				}
			}
		}
	}
	while (check_correct_input == false);
	return false;
}

bool check_exit(char *var_fav)
{
	int value_cmp_exit = strcmp(mexit, var_fav);

	if (value_cmp_exit == 0)
	       return true;
	else
		return false;	
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

void get_fav(FILE *file)
{
	char * fav;
	printf("Please past or write your note: \n");

	fav = get_string();

	int len = strlen(fav);

	if (len == 0)
	{
		printf("Your note is empty. Action cancelled.\n");
		free(fav);
		exit(2);
	}

	if (check_exit(fav) == true)
	{
		free(fav);
		exit(0);
	}

	fprintf(file, "%s|END|", fav);
	free(fav);
}

char * get_tag()
{
	bool check_len = false;
	//check if the user put special char. If it is the case, return error.
	bool check_alpha = false;
	char * tag;

	do
	{
		check_alpha = true;

		tag = get_string();

		int len = strlen(tag);

		if (len == 0)
		{
			printf("Fail: your tag is empty.\n");
			free(tag);
		}
		else if (len >= 50)
		{
			printf("Fail: the maximum lenght of a tag is 50 char.\n");
			free(tag);
		}

		else
		{
			check_len = true;

			for (int i = 0; i < len; i++)
			{
				if (!(isalpha(tag[i])))
					check_alpha = false;
			
				if (isupper(tag[i]))
					tag[i] = tolower(tag[i]);
			}
			
			if (check_alpha == false)
			{
				printf("Fail: Your tag must have only letters.\n");
				free(tag);
			}
		}
	}
	while (check_alpha != true || check_len != true);
	
	return tag;
}

int list_tag(FILE * file)
{
	int i = 0;

	//have to declare this variable here because of the do while loop.
	int cmp_stop = 1;
	int cmp_s = 1;

	//Check if the user put at least one tag. If not, prompt again.
	bool check_tag = false;

	char * list_tag[30];

	printf("Please enter tags one by one, enter 'stop' when you finish: \n");

	do
	{
		int cmp_same_word = 1;
		char * var_tag = get_tag();
		bool check_tag_exist = false;

		cmp_stop = strcmp(var_tag, mstop);
		cmp_s = strcmp(var_tag, s);

		if ((cmp_stop == 0|| cmp_s == 0) && check_tag == false)
			printf("You have to put at least one tag, because it is the only way to find your note.\n");

		list_tag[i] = var_tag;

		if (i > 30)
		{
			printf("You can't have more than 30 tags.\n");
			for (int j = 0; j < i; j++)
				free(list_tag[j]);

			return 1;
		}

		// Check if the tag was already type by the user. If not, add the tag to the file.
		for (int j = 0; j < i; j++)
		{
			cmp_same_word = strcmp(list_tag[i], list_tag[j]);
			if (cmp_same_word == 0 && (cmp_stop != 0 && cmp_s != 0) && check_tag_exist != true)
			{
				printf("You already enter this tag.\n");
				check_tag_exist = true;
			}
		}

		if (check_tag_exist != true && cmp_stop != 0 && cmp_s != 0)
		{
			fprintf(file, "<%s>", list_tag[i]);
			check_tag = true;
		}

		i++;
	}
	while ((cmp_stop != 0 && cmp_s != 0) || check_tag == false);

	for (int j = 0; j < i; j++)
		free(list_tag[j]);

	if (check_tag == true)
	{
		fprintf(file, "|END|");
		return 0;
	}
	else
		return 1;
}

int add_comment(FILE *file)
{
	char * comment;
	char * answer_comment;
	char yes[4] = "yes";
	char no[3] = "no";
	char y[2] = "y";
	char n[2] = "n";
	//check if the answer for adding a comment is correct. If not, re-prompt the user.
	bool check_comment = false;

	printf("Do you want to add a comment ? (y/n)\n");
	do
	{
		bool check_alpha = true;

		answer_comment = get_string();

		int answ_len = strlen(answer_comment);

		for (int i = 0; i < answ_len; i++)
		{
			if (!(isalpha(answer_comment[i])))
				check_alpha = false;

			if (isupper(answer_comment[i]))
				answer_comment[i] = tolower(answer_comment[i]);

		}	

		int cmpYes = strcmp(answer_comment, yes);
		int cmpY = strcmp(answer_comment, y);
		int cmpNo = strcmp(answer_comment, no);
		int cmpN = strcmp(answer_comment, n);
		int cmpExit = strcmp(answer_comment, mexit);

		if (check_alpha == false)
		{
			printf("Fail: your answer contains special characters.\n");
			free(answer_comment);
			check_comment = false;	
		}

		else if (answ_len > 5)
		{
			printf("Too much character.\n");
			free(answer_comment);
			check_comment = false;
		}

		else if (cmpYes == 0||cmpY == 0)
		{
			free(answer_comment);
			//check if the comment is empty.
			bool check_correct_comment = false;

			printf("Please enter your comment:\n");
	
			do
			{
				comment = get_string();

				int len_comment = strlen(comment);
				int cmpStop = strcmp(mstop, comment);
				int cmpS = strcmp(s, comment);

				if (len_comment == 0)
				{
					printf("Fail: your comment is empty. Enter 'stop' to cancel adding comment.\n");
					check_correct_comment = false;
					free(comment);
				}

				else if (cmpStop == 0||cmpS ==0)
				{
					free(comment);
					return 0;
				}

				else
				{
				fprintf(file, "'%s'", comment);
				fprintf(file, "|END|\n");
				check_comment = true;
				check_correct_comment = true;
				free(comment);
				return 0;
				}
			}
			while (check_correct_comment != true);
		}
		else if (cmpNo == 0||cmpN == 0)
		{
			check_comment = true;
			fprintf(file, "\n");
		       	return 0;
		}
		else if (cmpExit == 0)
		{
			check_comment = true;
			return 0;
		}
		else
		{
			printf("Invalid choice\n");	
			check_comment = false;
		}
	}
	while (check_comment != true);
	return 1;
}

