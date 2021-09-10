#include <stdio.h>
#include <string.h>

#include "priority_q.h"
#include "test_functions.h"

/****************************************************************************/

typedef struct student
{
    char* name;
    int age;
}student_t;

int is_name_before(const void* student1, const void* student2, const void* param)
{
    char* name1 = ((student_t*)student1)->name;
    char* name2 = ((student_t*)student2)->name;
	param = param;

    return (strcmp(name1, name2) < 0);
}

int match(const void* student, const void* param)
{
    return ((student_t*)student)->name[0] != *(char*)param;
}

/****************************************************************************/

void UgliestTestEver() 
{
	size_t i = 0;
    student_t students[] = {{"pasha", 32},
	{"aviv", 37}, {"sergei", 30}, 
	{"eliraz", 31}, {"achinoam", 27}, {"shira", 29}, 
	{"lidan", 29}};
    char ch = 's';

    pq_t* list_by_name = PQCreate(&is_name_before, NULL);

    VerifySizeT(PQSize(list_by_name), 0, "Size");
    VerifyInt(PQIsEmpty(list_by_name), 1, "IsEmpty");

    for (i = 0; i < sizeof(students)/sizeof(students[0]); i++)
	{
		PQEnqueue(list_by_name, &students[i]);
	}

    VerifyPointer(PQPeek(list_by_name), &students[4], "Enqueue, Peek");
    VerifyPointer(PQDequeue(list_by_name), &students[4], "Dequeue");
    VerifySizeT(PQSize(list_by_name), 6, "Dequeue, Size");
    VerifyInt(PQIsEmpty(list_by_name), 0, "IsEmpty");
    VerifyPointer(PQPeek(list_by_name), &students[1], "Dequeue, Peek");

    while (PQErase(list_by_name, &match, &ch))
    {
    }

    VerifySizeT(PQSize(list_by_name), 4, "Erase");
    VerifyPointer(PQPeek(list_by_name), &students[1], "Erase, Peek");
    PQClear(list_by_name);
    VerifyInt(PQIsEmpty(list_by_name), 1, "Clear");
    PQDestroy(list_by_name);
}

int main()
{
    UgliestTestEver();

    return 0;
}