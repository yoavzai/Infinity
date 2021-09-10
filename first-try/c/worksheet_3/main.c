#include <stdio.h>
#include <stdlib.h> /* free */
#include "exercise.h"



int main(int argc, char** argv, char** envp)
{
	if (argc != 2)
	{
		printf("Enter number of soldiers\n");
		return 0;
	}

	/* copy and print envp in lowercase */

	{
		char** buffer;
		buffer = CpyArrOfStr((const char**)envp);

		PrintArrOfStr((const char**)buffer);
		free(buffer);
		printf("------------------\n");
	}

	/* Josephus Problem */
	
	printf("The last soldier standing is soldier ");
	printf("%lu\n", Josephus(argv[1]) + 1);
	printf("------------------\n");
	
	/* Print Data Types */

	PrintTypes();
	
	
	return 0;
}
