#ifndef POLY
#define POLY
#include <stddef.h>

enum data_type_t {TYPE_EMPTY, TYPE_INT, TYPE_FLOAT, TYPE_STR};

typedef struct data
{
	enum data_type_t type;

	union
	{	
		char* str;
		int d;
		float f;
	}value;

}Data_t;

void PolySetValue(Data_t* elem, enum data_type_t set_type,const void* value_p);
void PolyAdd(Data_t* elem, int num);
void PolyPrintSingle(Data_t* elem);
void PolyPrintAll(Data_t* elem, size_t size);
void PolyCleanSingle(Data_t* elem);
void PolyCleanAll(Data_t* elem, size_t size);


#endif
