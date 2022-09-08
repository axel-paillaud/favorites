# notes.c
#### Video Demo:  <https://youtu.be/HimcuEzp828>
#### Description:
  
**Summary**

The purpose of this program is to save textual notes in a file, and to associate keywords (called “tags”) in order to find these notes easily. These notes can be, for example, a link to a site, a code phrase or a function that is used often, or even an entire paragraph. There is no limit on the number of characters for the note (thanks to malloc, we will come back to this).  
It's similar to the Evernote software for example, or even Notion with the use of tags, but everything happens on the command line, in the Terminal.  
The program is entirely written in C, and since it is used via the terminal, it is very light and very fast.  


**Explanation**

The program starts by asking the user if you want to add a note, or search for a note already written, this is the **`add_or_search` function**:

- The user must type 'a' or 'add' or add a note, 's' or 'search' to search for a note.  
- If the user types too many characters, the program refuses the input with an error message, using the **`strlen()`** function.  
- If the user types special characters, the program refuses the input with an error message. For this, it uses the **`isalpha()`** function with a Boolean variable in a loop on each of the letters.  
- If a character is uppercase, the program changes it to lowercase with the **`isupper()`** and **`**tolower()`** function. We can therefore write Add as add.  
- If the input is correct, the program will compare the user's character string with arrays already written: search, s, add, a, with the **`strcmp()`** function.  
- If strcmp returns 0 on search or s, the **`add_or_search()`** function returns **true** (true = search).  
- If strcmp returns 0 on add or a, the **`add_or_search()`** function returns **false** (false = add).  
- If strcmp returns a number other than 0, then the input is incorrect and the function prompts the user again.  

At any time, the user can quit the program by writing exit, stop or s, with the function **`bool check_exit_stop(char *string)`**. This uses the same string comparison tools as the **`add_or_search`** function, along with **strcmp.**

If the user wishes to add a note, the program will create a **.notes_db** file in **“append”** mode if it does not exist, and open the file if it already exists.

function **`char * get_string(void)`**:
Every time the program asks for an input from the user, I use this **get_string** function. It is particularly well written and effective and is not mine, I thank MIT professor James Aspnes for having published it in an online course. Before that, I used **`scanf()`** or even **`fgets`** and I had a lot of known problem with these two functions.  

**explanation of `get_string()` function**:  
- This one malloc a pointer called **string** of type **char** of size 2.  
- We initialize a variable length (of text) to **0**.  
- Then, we use the **`getchar()`** function in a **while** loop, as long as getchar is not equal to **'\n'** or to **EOF** (so as long as we have not reached the end of the user's input).  
- We associate the current character with the **string** pointer, then we increment by 1 length with the syntax **`string[length++] = c`**.  
- In the loop, if **length** is greater than the size of the string pointer (so here, 2), then this size is multiplied by two and we realloc the pointer. We get 4, if we exceed 4, we get 8, etc.  
- When we reach **'\n'**, we exit the loop. The program then adds **'\0'** at the end of the string, in order to indicate that it is indeed the end of the character string. Then it returns string.  

The only “downside” to this function is that you have to use **`free()`** because it uses **malloc**.

- If the user wants to add a note, the program first calls the function **`void get_fav(FILE *file)`**:  
- The user is asked to write or paste his note by calling the **`get_string`** function.  
- If the input is empty (strlen = 0), the program sends an error message, frees **`get_string`** and exits the program. You cannot save an empty note.  
- Otherwise, the program adds the user's input to the hidden **.notes_db** file, followed by the **|END|** keyword, with the **`fprintf();`** function. 

Explanation of the **|END|** keyword:  
- When you want to search for a note in the **.notes_db file**, the program will use a function described later, **`strpart`**, which will split a string at each **|END|** keyword. He therefore knows if it is the first part, therefore the **note**, the second part, therefore the **tags**, or the third part, therefore the **comments** (a comment can be added at the end, if we just wrote a link for example.).  
- I used such a keyword because one can be almost sure that the user will never write **|END|** in his note. At the beginning, I had used commas in a CSV file, but it was quickly problematic when the user entered commas, and we don't really need a CSV file here (we won't enter the data in a table ,It is not the goal).  

Next, the program asks to associate **tags**, with the **`char * get_tag()`** function:  
- This function is used to retrieve a tag, and will check if all the conditions are ok before returning the tag.  
- If the tag is empty, error message, then prompt again.
- If the tag is longer than 50 characters, error message, then prompt again (no word that I know of is longer than 50 characters).  
- If the user wrote as tag **exit**, the program sends an error message. Indeed, it is the keyword to exit the program when looking for notes, so it cannot be used as a tag.
- Then, the function checks on each letter if the input contains a special character, with the same technique as in the add_or_search function. A tag can only have letters.  
- This brings a disadvantage, you cannot add a letter with accent in a tag. Point of improvement in a future update (if there is one :p).  
- Finally, if all the conditions are ok, the function returns a string **tag**.


The program will then save these tags in a pointer array, with the **`int list_tag(FILE *file)`** function:  
- First, some condition checks:  
    - If no tag, error message, at least one tag is needed because it is the only way to find the note afterwards. prompt again.  
    - If more than 30 tags, error message, the maximum is 30 tags (this is more than enough). The memory is freed, the program is stopped.  
- Then the program will compare all the elements of the tag array (**`char * list_tag[30]`**) to see if two tags are not identical.  
- If this is not the case, then the function adds the tag to the **.notes db** file with the **`fprintf()`** function and by adding a comma at the end of the tag. This is what separates each tag and allows the program to separate them later.  
- At the end, we add **|END|** again.  

The program completes the note addition by asking the user if they want to add a comment with the **`int add_comment(FILE *file)`** function:  
- I won't go into too much detail here because it's the same techniques used previously (check multiple conditions, if input ok, add to file, followed by the keyword **|END|**).  
- To tell the truth, after the fact, I wonder about the usefulness of this feature. It could potentially be deleted, but now that I've written it, for now I leave it ^^.  

**SEARCH**

If the user wants to search for a note already written, the program will open the .**notes_db** file in read (“**r**”) mode. If the file does not exist, an error message is sent and the program terminates. If this exists:

The program will first count the number of notes with the function **`int compute_nbr_of_notes(FILE *file)`** This is information that will be very useful to us:  
- It will read the file character by character with the **`fgetc()`** function. If the character is equal to **'\n'**, then it is a new line and therefore a new note.

The program will then add each note, tag and comment in a **struct notes** composed of 3 fields:  
1. **`char * note`**, corresponds to the note.  
2. **`char * comment`**, corresponds to the comment.  
3. **`char * arr_tag[30]`**, corresponds to the tag array.  
  
It will create an array of this struct of the size of the number of notes thanks to the previous function **`compute_nbr_of_notes`**.

To do this, it will use a (too) large function, called **`void add_file_to_arr_notes(FILE *file, notes *arr_notes, int nbr_of_notes)`**: 

- It will first count the number of characters in a line (therefore in a note, tag, comment set), in order to create an array containing only this line.  
- Then, the **strpart** function will separate this line into 3 parts: one for the **note**, one for the **tags**, one for the **comment** if there is one.  

**explanation of `char * strpart(char lines[], char separator[], int section)` function**:  
- This function takes three arguments:  
    - A line, therefore an entire string, containing separator keywords.  
    - A separator keyword, in our case **|END|**.  
    - A section, to know if you want to get the first part, the second etc.  
- Then, a variable **`char check_separator[]`** of the size of the separator (so here 5) is created.  
- The function will then advance letter by letter in the line. The **check_separator** variable will always be 5 characters ahead of the line (with the use of nested for loops), and will compare this data with the separator sought.  
- If the **check_separator** variable is equal to the **separator** variable, then a separator has been reached.  
- If we are in the desired section, then we malloc a string of the size necessary to handle this part, then we return this part.  
- Otherwise, we repeat the operation until we are in the right part.  
- If ever we never find the separator (for example, because there is none, or we indicated the wrong separator), we will quickly find ourselves in an infinite loop, which is moreover risk of malloc the memory for nothing.  
- The fonction can handle this. The check_separator variable will quickly fill with **'\0'**. If this happens, the function stops and returns **NULL**.  

Back to the **`add_file_to_arr_notes`** function. So we get the first part of our line, here the note:  
- If **strpart** is equal to **NULL**, then this note is ignored and the current index of the array struct notes points to **NULL** and will be ignored.  
- Otherwise, we malloc a variable **`char note`**, and we make the field of the **`struct notes.note`** point to this variable. So the pointer to the **`struct notes.note`** is equal to a **`note`**.  
- Next, we need to add the tags. We extract the tags from this line with the **`strpart`** function, then we count the number of tags by counting the commas.    
- In a **for loops** which will repeat the sequence as many times as there are tags, we malloc a tag and we copy each character into it, as long as we have not reached the comma (in a **do-while** loop ).  
- Once we have reached the comma, therefore the end of the tag, we add it to the array **`arr_tag`** of the **`struct notes`**. We point the following **`arr_tag`** to **NULL** to indicate that, for the moment, there is no tag after (if there is a tag after, the **NULL** pointer will be replaced by this one, then the **`arr_tag`** next will point to **NULL**, etc).  
- We do this for all tags.  

We use the same strategy for comments.

When this function is complete, sufficient memory for all notes, tags, and comments has been dynamically allocated in the computer's RAM. This will greatly facilitate the note search, no more need to break down the file, we just have to follow the pointers.

**`void search_notes(int nbr_of_notes, notes *arr_notes)`**:  
Comes the time to look for the notes. I had initially thought of implementing a **hash table**, this would have been possible by hashing the tags for example to obtain a numerical value and put it into an array, then creating a linked list from one note to another.  
I finally chose a simple **linear search** . Indeed, even if the **.notes db** file contains 300 notes, and these each contain 30 tags (unlikely), that makes 9,000 items to search for. On a C program it will take less than a second, but I haven't tested on old machines.

function description:  
- The user is asked to enter one or more tags, separated by a space.  
- First, a series of conditions with the classic convert uppercase to lowercase, check for special character, etc.  
- If only one tag is written, then the **linear search** begins immediately.  
    - For each note, we will look at each tag, one by one, and check that one of them matches the user's input tag.  
    - If this is the case, then we print the note on the screen, with its comment if there is one.  
- If several tags have been written:  
    - We add these in an array.  
    - We create an **array arr_check_find** of **boolean** type, the size of the number of tags that has been written.  
    - For each note, we compare each tag with the user's input tag array. If a tag matches, we set the value of the current index of the array **arr_check_find** to **true**.  
    - If all the values ​​of the **arr_check_find** array are equal to true, then the note contains all the tags that the user entered in input. We can therefore display the note on the screen.  

**`void print_decoration(char decoration, int nbr)`**:  
This small function is used to add aesthetic lines in order to separate the different notes that have been found. You can change the character or the number (= line size) easily by modifying the arguments.

**`void free_arr_notes(notes *arr_notes, int nbr_of_notes)`**: 
This function is very important, and is of course used to free the memory of all notes, tags and comments (aka struct notes), using a simple loop.


**Points that could be improved:**
- Accept accents.  
- Implement a **hash table** if slowing down on very large files or on old machine.
- Maybe remove the commentary.  
- The add or search choice could be removed, by directly offering the user to enter a note. If it writes search, then we go into search mode.  
- Some functions are too long and become complicated to modify. I should have created smaller functions.  
- In the **`search_notes`** function, I embed too many if, else conditions in a not always logical way.  

**difficulties encountered:**  
- A lot of wasted time finding an efficient function to get a string from the user.  
- A huge memory leak due to the strpart function which did not take into account the fact of not finding any keywords, and which malloc indefinitely in a loop.  Difficult to find the origin of the leak.  
- Choice between hash table and linear search.

**some numbers:** 

- number of all-inclusive hours to complete this program:   
about 70 hours  

- number of lines of code:  
1048  

- number of functions:  
14  


**my satisfactions:**

no leaks of memory after many tests with Valgrind (obligatory but I specify it anyway).

It is certainly possible to encounter bugs that I do not know yet. Nevertheless, the program is stable and is able to react to many different situations, even if the user does not cooperate.

The program is written in C, and even if the result is not visually impressive, it is quite a challenge to write.
