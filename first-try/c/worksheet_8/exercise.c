#include <stdio.h>

#define MAX2(a, b) (a) > (b) ? (a) : (b)
#define MAX3(a, b, c) MAX2(a, b) > (c) ? MAX2(a, b) : (c)
#define SIZEOF_VAR(x) (char*)(&x + 1) - (char*)(&x)
#define SIZEOF_TYPE(type) (((type*)0)+1)


int main()
{	
	int x = 5;

	printf("%f\n", MAX2(3.1213, 4.12));
	printf("%c\n", MAX3('A', 'b', '~'));
	printf("Size of x is : %lu\n", SIZEOF_VAR(x));
	printf("Size of short is : %lu\n", SIZEOF_TYPE(short));	 

	return 0;
}
