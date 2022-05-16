#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INITIAL_STRING_LENGTH (2)

//struct
typedef struct notes 
{
	char * note;
	char * comment;
	char * arr_tag[30];
}
notes;

//prototype
char * get_string(void);
bool search_or_add();
bool check_exit(char * var_fav);
void get_fav(FILE *file);
char * get_tag();
int list_tag(FILE * file);
int add_comment(FILE *file);
int compute_nbr_of_notes(FILE *file);
void insert_comment(notes *arr_notes);
void add_file_to_arr_notes(FILE* file, notes *arr_notes, int nbr_of_notes);
void free_arr_notes(notes *arr_notes, int nbr_of_notes);
char * strpart(char lines[], char separator[], int section);
void search_notes(int nbr_of_notes, notes *arr_notes);
void print_decoration(char decoration, int nbr);

// global variable
char mexit[5] = "exit";
char mstop[5] = "stop";
char s[2] = "s";
char *note;
char *tag;
char *comment;

int main(void)
{
	bool check_search_or_add = search_or_add();

	if (check_search_or_add == true)
	{
		FILE *file = fopen(".notes.db", "r");
		if (file == NULL)
		{
			printf("Impossible to read the notes files.\n");
			return 1;
		}

		int nbr_of_notes = compute_nbr_of_notes(file);

		notes arr_notes[nbr_of_notes];

		add_file_to_arr_notes(file, arr_notes, nbr_of_notes);

		search_notes(nbr_of_notes, arr_notes);

		free_arr_notes(arr_notes, nbr_of_notes);

		fclose(file);
	}

	else
	{
		FILE *file = fopen(".notes.db", "a");
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
		else if(check_exit(tag))
		{
			printf("Error: sorry, a tag cannot be exit, because it is the key word to exit the program.\n");
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
	while (check_alpha != true||check_len != true||(check_exit(tag)) == true);
	
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
			fprintf(file, "%s,", list_tag[i]);
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
				fprintf(file, "%s", comment);
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

int compute_nbr_of_notes(FILE *file)
{
	int lines = 0;
	char c;

	do
	{
		c = fgetc(file);
		
		if (c == '\n')
			lines ++;
	}
	while(c != EOF);

	return lines;
}

void insert_comment(notes *arr_notes)
{
	char * phrase = "Une phrase";
	char * phrase2 = "une autre phrase";
	int x = 1;
	int y = 2;

	arr_notes[x].comment = phrase;
	arr_notes[y].comment = phrase2;

}

void add_file_to_arr_notes(FILE* file, notes *arr_notes, int nbr_of_notes)
{
	char c;
	char *comment;
	char *tmp_part;
	char separator[6] = "|END|";

	rewind(file);

	//For each notes, do
	for (int i = 0; i < nbr_of_notes; i++)
	{
		int len_lines = 0;

		//while the note isn't finish, do 
		//first, count the nbr of char of one line
		do
		{
			c = fgetc(file);
			len_lines++;
		}
		while(c != '\n' && c != EOF);

		//rewind back to the beginning of the line
		fseek(file, -len_lines, SEEK_CUR);

		//create the line array, then add char to this array
		char lines[len_lines + 1];

		int cur_pos = 0;
		do
		{
			c = fgetc(file);
			lines[cur_pos] = c;
			cur_pos++;
		}
		while(c != '\n' && c != EOF);

		lines[len_lines] = '\0';

		tmp_part = strpart(lines, separator, 1);

		int size_note = strlen(tmp_part);

		note = malloc(size_note * sizeof(char));

		strcpy(note, tmp_part);

		arr_notes[i].note = note;

		free(tmp_part);

		tmp_part = strpart(lines, separator, 2);

		//count the number of tag
		int nbr_of_tag = 0;
		int z = 0;
		do
		{
			c = tmp_part[z];
			if(c == ',')
				nbr_of_tag++;
			z++;
		}
		while(c != EOF && c != 0);

		//add each tag to the array .tag of struct notes.
		int tmp_pos = 0;
		for (int x = 0; x < nbr_of_tag; x++)
		{
			int j = 0;
			tag = malloc(50 * sizeof(char));
			do
			{
				c = tmp_part[tmp_pos];
				tag[j] = c;
				tmp_pos++;
				j++;
			}
			while(c != ',' && c != EOF);

			tag[j-1] = '\0';	

			arr_notes[i].arr_tag[x] = tag;

			arr_notes[i].arr_tag[x + 1] = NULL;
		}

		free(tmp_part);

		//if comment, add comment
		tmp_part = strpart(lines, separator, 3);
		char check_comment;
		check_comment = tmp_part[0];
		if (check_comment == '\n')
		{
			arr_notes[i].comment = NULL;
			free(tmp_part);
		}
		else
		{
			int size_comment = strlen(tmp_part);
			comment = malloc(size_comment * sizeof(char));
			strcpy(comment, tmp_part);
			arr_notes[i].comment = comment;
			free(tmp_part);
		}
	}
}

void free_arr_notes(notes *arr_notes, int nbr_of_notes)
{
	//for each notes, free note
	for (int i = 0; i < nbr_of_notes; i++)
	{
		if (arr_notes[i].note != NULL)
			free(arr_notes[i].note);

		//for each tag, free tag
		int j = 0;
		char *ptr; 
		do
		{
			ptr = arr_notes[i].arr_tag[j];
			free(ptr);
			j++;
		}
		while(ptr != NULL);

		//for each comment, free comment
		if (arr_notes[i].comment != NULL)
			free(arr_notes[i].comment);
	}
}

char * strpart(char lines[], char separator[], int section)
{
	char * part;
	char n = 'a';
	int cmp_separator = 1;
	int cur_pos = 0;
	int size_separator = 0;
	int cmp_section = 1; //check if the section arg correspond to the current section

	for (int i = 0; n != '\0'; i++)
	{
		n = separator[i];
		size_separator++;
	}

	if(size_separator > 10)
	{
		printf("Error, the separator is too long.\n");
		exit(10);
	}

	char check_separator[size_separator];

	//which token to get
	for(int i = 0; i < section; i++)
	{
		//length of the part we need
		int len = 0;
		while(cmp_separator != 0)
		{
			for(int j = 0; j < size_separator; j++)
			{
				check_separator[j] = lines[cur_pos + j];
			}

			check_separator[size_separator - 1] = '\0';

			cmp_separator = strcmp(check_separator, separator);

			len++;
			cur_pos++;	
		};
		
		cmp_separator = 1;
		//if we are in the section we wanted, malloc and return the strpart. Else, do it again until we are in the section we wanted.
		if(cmp_section == section)
		{
			part = malloc(len * sizeof(char));
			char tmp[len];

			cur_pos -= len;

			int n = 0;

			while(cmp_separator != 0)
			{

				for(int j = 0; j < size_separator; j++)
				{
					check_separator[j] = lines[cur_pos + j];
				}

				check_separator[size_separator - 1] = '\0';

				tmp[n] = lines[cur_pos];
				n++;

				cmp_separator = strcmp(check_separator, separator);

				cur_pos++;
			}

			tmp[len - 1] = '\0';

			strcpy(part, tmp);

			return part;
		}
		else
		{
			cmp_section++;
			cur_pos += (size_separator - 2);
		}
	}
	part = NULL;
	return part;
}

void search_notes(int nbr_of_notes, notes *arr_notes)
{
	char * input;
	char space = ' ';
	char separator[2] = " ";
	char *tag_cmp;
	char c;
	int input_len;
	int tag_len;
	int cmp_value;
	bool check_special_char = false;
	bool check_correct_input = false;
	bool var_check_exit = false;
	char * search_tag[30];
	char * tag;
	int nbr_of_search_tag = 1;
	int part = 1; // for the function strpart

	do
	{
		printf("Please enter some tags: \n");

		do
		{
			input = get_string();

			var_check_exit = check_exit(input);
			
			input_len = strlen(input);

			if(var_check_exit != true)
			{
				
			}
			//check for special char EXCEPT for space, convert uppercase to lowercase, count nbr of tag, check if nbr of tag < 30.
			for(int i = 0; i < input_len; i++)
			{
				c = input[i];	
				if(isupper(c))
					input[i] = tolower(c);
		
				if(!(isalpha(c)) && c != space)
					check_special_char = true;

				if(c == space && (input[i + 1] != '\0'))
					nbr_of_search_tag++;
			}	

			if(check_special_char == true)
			{
				printf("Fail: your tag must have only letters.\n");
				check_correct_input = false;
				free(input);
			}
			else if(input_len == 0)
			{
				printf("Fail: empty tag.\n");
				check_correct_input = false;
				free(input);
			}
			else if(nbr_of_search_tag > 30)
			{
				printf("Fail: too much tags.\n");
				check_correct_input = false;
				free(input);
			}
			else
				check_correct_input = true;
		}
		while(check_correct_input == false);

		//if only one tag, do simple linear search
		if(nbr_of_search_tag == 1 && var_check_exit != true)
		{
			tag = input;

			tag_len = strlen(tag);

			//check if tag is not > 50
			if(tag_len > 49)
			{
				printf("A tag cannot be longer than 50 char.\n");
				free(tag);
				exit(4);
			}	

			//check if last char isn't space. If, remove it.
			if(tag[tag_len - 1] == space)
				tag[tag_len - 1] = '\0';	

			printf("\n");
			//linear search
			//for each notes
			for(int i = 0; i < nbr_of_notes; i++)
			{
				bool check_find = false;
				int j = 0;

				//for each tag
				do
				{
					tag_cmp = arr_notes[i].arr_tag[j];
					cmp_value = strcmp(tag_cmp, tag);
					
					if(cmp_value == 0)
					{
						//print some decoration
						print_decoration('-', 35);
						printf("%s\n", arr_notes[i].note);

						if(arr_notes[i].comment != NULL)
							printf("'%s'\n", arr_notes[i].comment);

						print_decoration('-', 35);

						printf("\n");

						check_find = true;
					}
					j++;
				}
				while((j < 30) && (arr_notes[i].arr_tag[j] != NULL) && (check_find != true));
			}
			free(tag);
		}
		else
		{
			//add each tags to the array search_tag
			for(int i = 0; i < nbr_of_search_tag; i++)
			{
				tag = strpart(input, separator, part);
		
				//check if tag is not > 50
				tag_len = strlen(tag);
				if(tag_len > 50)
				{
					printf("A tag is longer than 50 char and is ignored.\n");
					search_tag[i] = NULL;
					search_tag[i + 1] = NULL;
					free(tag);
				}
				else
				{
				search_tag[i] = tag; // Penser à free toute l'array search_tag
				search_tag[i + 1] = NULL;
				part++;
				}
			}
			//linear search
			//for each notes, do
			for(int cur_note = 0; cur_note < nbr_of_notes; cur_note++)
			{
				bool arr_check_find[nbr_of_search_tag];
				for(int set_false = 0; set_false < nbr_of_search_tag; set_false++)
				{
					arr_check_find[set_false] = false;
				}

				//for each search tag, do
				for(int cur_search_tag = 0; cur_search_tag < nbr_of_search_tag; cur_search_tag++)
				{					
					//for current tag inside arr_notes
					int j = 0;

					do
					{
						tag = search_tag[cur_search_tag];
						tag_cmp = arr_notes[cur_note].arr_tag[j];
						cmp_value = strcmp(tag, tag_cmp);

						if(cmp_value == 0)
						{
							arr_check_find[cur_search_tag] = true;
						} 
						j++;
					} while (arr_notes[cur_note].arr_tag[j] != NULL);					
				}

				//check if all the bool arr_check_find is true
				bool check_find = true;
				for(int chk = 0; chk < nbr_of_search_tag; chk++)
				{
					if(arr_check_find[chk] == false)
					check_find = false;
				}
					
				//print if all tag is found
				if(check_find == true)
				{
					printf("\n");
					print_decoration('-', 35);
					printf("%s\n", arr_notes[cur_note].note);
					
					if(arr_notes[cur_note].comment != NULL)
						printf("'%s'\n", arr_notes[cur_note].comment);
						print_decoration('-', 35);
				}
			}
			printf("\n");
		}
		//free search_tag
		for(int i = 0; i < nbr_of_search_tag; i++)
		{
			free(search_tag[i]);
		}
	}
	while(var_check_exit != true);
}

void print_decoration(char decoration, int nbr)
{
	for(int star = 0; star < nbr; star++)
	{
		printf("%c", decoration);
	}
	printf("\n");
}










