#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Poly.h"

int main()
{
	Data_t my_arr[4];
	int n = 56;
	float f = 23.346;
	
	printf("\nset 0:\n");
	PolySetValue(&my_arr[0], TYPE_STR, "hello");
	PolyPrintSingle(&my_arr[0]);
	
	printf("\nset 1:\n");
	PolySetValue(&my_arr[1], TYPE_INT, &n);
	PolyPrintSingle(&my_arr[1]);
	
	printf("\nset 2:\n");
	PolySetValue(&my_arr[2], TYPE_FLOAT, &f);
	PolyPrintSingle(&my_arr[2]);

	printf("\nset 3:\n");	
	PolySetValue(&my_arr[3], TYPE_STR, "HOw You DoiN'");
	PolyPrintSingle(&my_arr[3]);

	printf("\nprint all:\n");
	PolyPrintAll(my_arr, 4);
	
	printf("\nadd all:\n");
	PolyAdd(&my_arr[0], 44);
	PolyAdd(&my_arr[1], 44);
	PolyAdd(&my_arr[2], -23);
	PolyAdd(&my_arr[3], 123456);	
	PolyPrintAll(my_arr, 4);

	printf("\nclean 0:\n");
	PolyCleanSingle(&my_arr[0]);
	PolyPrintAll(my_arr, 4);
	
	printf("\nclean 1:\n");
	PolyCleanSingle(&my_arr[1]);
	PolyPrintAll(my_arr, 4);

	printf("\nclean all:\n");
	PolyCleanAll(my_arr, 4);
	PolyPrintAll(my_arr, 4);	

	return 0;
}

