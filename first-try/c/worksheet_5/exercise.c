#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARR_SIZE 5

enum state{finish, fail, success};

int IsSame(const char* str1, const char* str2)
{
	return strcmp(str1, str2);
}

int IsStartAppend(const char* str1, const char* str2)
{
	return strncmp(str1, str2, 1);
}

int IsAppend(const char* str1, const char* str2)
{
	(void)str1;
	(void)str2;

	return 0;
}

enum state Remove(const char* file_name, const char* str)
{
	(void)str;	
	
	if (remove(file_name))
	{
		return fail;
	}

	printf("%s removed. to recreate it start adding lines\n", file_name);

	return success;
}

enum state Count(const char* file_name, const char* str)
{
	FILE* fp = fopen(file_name, "r");
	char ch;
	size_t counter = 0;
	(void)str;

	if (!fp)
	{
		return fail;
	}

	ch = getc(fp);
	
	while (ch != EOF)
	{
		if (ch == '\n')
		{
			counter++;
		}		
		ch = getc(fp);
	}
	
	/* check if actual end of file has reached */
	if (feof(fp))
	{ 
    	printf("%s have %lu lines written in it\n", file_name, counter);
		fclose(fp);
		return success;
  	}

	/* something went wrong with getc */
	else
	{
    	return fail; 
	}
	
}

enum state Exit(const char* file_name, const char* str)
{
	(void)str;
	printf("Changes to %s are saved, Goodbye!\n", file_name);
	return finish;
}


enum state StartAppend(const char* file_name, const char* str)
{
	FILE* fp = fopen(file_name, "r");
	FILE* new = fopen("temp", "a");
	char ch;
	
	if (!fp || !new)
	{
		return fail;
	}
	
	fprintf(new, "%s", (str + 1));
 
	ch = getc(fp);

	while (ch != EOF)
	{
		putc(ch, new);
		ch = getc(fp);
	}
	
	remove(file_name);
	rename("temp", file_name);
 	fclose(fp);
	fclose(new);

	return success;
}

enum state Append(const char* file_name, const char* str)
{
	FILE* fp = fopen(file_name, "a");
	
	if (!fp)
	{
		return fail;
	}

	fprintf(fp, "%s", str);
	fclose(fp);

	return success;
}


struct action
{
	char* word;
	int (*compare)(const char*, const char*);
	enum state (*operate)(const char*, const char*);
	
};

int main(int argc, char** argv)
{
	
	struct action arr[ARR_SIZE] = {
	{"-remove\n", &IsSame, &Remove},
	{"-count\n", &IsSame, &Count},
	{"-exit\n", &IsSame, &Exit},
	{"<", &IsStartAppend, &StartAppend},
	{"", &IsAppend, &Append},
	};

	enum state cur_state = success;
	int i = 0;
	char* input = NULL;

	/* checks that user entered file name */
	if (argc != 2)
	{
		printf("Enter file name\n");
		return 0;
	}

	printf("print up to 1000 charecters per line and press Enter for a new line\n\
print \"<\" before line to add the line at the beginning of the file\n\
print \"-count\" to get the number of lines in the file\n\
print \"-remove\" to delete file\n\
print \"-exit\" to save file and exit the program\nBegin:\n");

	input = malloc(1000);
	
	while (cur_state)
	{
		fgets(input, 1000, stdin);
	
		for (i = 0; i < ARR_SIZE; ++i)
		{	
			if (!arr[i].compare(arr[i].word, input))
			{
				cur_state = arr[i].operate(argv[1], input);
				break;
			}
		}

		if (cur_state == fail)
		{
			printf("Something went wrong\n");
			break;
		}
	}

	free(input);

	return 0;
}






