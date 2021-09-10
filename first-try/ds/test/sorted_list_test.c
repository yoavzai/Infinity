#include <stdio.h>
#include <string.h>

#include "sorted_list.h"
#include "test_functions.h"

#define RESET "\033[0m"

/****************************************************************************/

typedef struct student
{
    char* name;
    int age;
}student_t;

void PrintList(srlist_t* list)
{
	int age = 0;
	char* name = NULL;
	sorted_list_iter_t iter1 = SortedListBegin(list);
	
	printf(RESET"\n");
	while (!SortedListIsSameIter(iter1, SortedListEnd(list)))
	{
		age = ((student_t*)SortedListGetData(iter1))->age;
		name = ((student_t*)SortedListGetData(iter1))->name;
		printf("%s, %d\n",name, age);

		iter1 = SortedListNext(iter1);
	}
	puts("");
}

int is_name_before(const void* student1, const void* student2, const void* param)
{
    char* name1 = ((student_t*)student1)->name;
    char* name2 = ((student_t*)student2)->name;
	param = param;

    return (strcmp(name1, name2) < 0);
}

int is_age_before(const void* student1, const void* student2, const void* param)
{
    int age1 = ((student_t*)student1)->age;
    int age2 = ((student_t*)student2)->age;
	param = param;
	
    return age1 < age2;
}

int Operation(void* student, void* limit)
{
	if (((student_t*)student)->age > *(int*)limit)
	{
		(((student_t*)student)->age /= 2);
	}

	if (!strcmp(((student_t*)student)->name, "yoav"))
	{
		return 1;
	}

	return 0;
}

/****************************************************************************/

void UgliestTestEver() 
{
	size_t i = 0;
    student_t students[] = {{"yoav", 34}, {"pasha", 32},
	{"aviv", 37}, {"yoni", 33}, {"tal", 35}, {"sergei", 30}, 
	{"eliraz", 31}, {"achinoam", 27}, {"shira", 29}, {"eran", 30}, 
	{"lidan", 29}};
		
    sorted_list_iter_t iter1;
    sorted_list_iter_t iter2;   
    srlist_t* list_by_name = SortedListCreate(&is_name_before, NULL);
	srlist_t* list_by_name2 = SortedListCreate(&is_name_before, NULL);
    srlist_t* list_by_age = SortedListCreate(&is_age_before, NULL);
	srlist_t* list_by_age2 = SortedListCreate(&is_age_before, NULL);

    VerifySizeT(SortedListSize(list_by_name), 0, "Size");
    VerifyInt(SortedListIsEmpty(list_by_age), 1, "IsEmpty");

    iter1 = SortedListBegin(list_by_age);
    iter2 = SortedListEnd(list_by_age);

	VerifyInt(SortedListIsSameIter(iter1, iter2), 1, "IsSameIter, Begin, End");
	VerifyPointer(SortedListGetData(iter1), NULL, "GetData");

	for (i = 0; i < sizeof(students)/sizeof(students[0]); i++)
	{
		SortedListInsert(list_by_age, &students[i]);
	}

	VerifySizeT(SortedListSize(list_by_age), 11, "Size");
    VerifyInt(SortedListIsEmpty(list_by_age), 0, "IsEmpty");

	iter1 = SortedListFind(list_by_age, SortedListBegin(list_by_age), 
								SortedListEnd(list_by_age), &students[0]);
	iter1 = SortedListNext(iter1);
								
	VerifyInt(((student_t*)(SortedListGetData(iter1)))->age, 35, "Find, Begin, End, GetData, Next");
	iter1 = SortedListPrev(iter1);
	iter1 = SortedListPrev(iter1);
	iter1 = SortedListPrev(iter1);
	VerifyString(((student_t*)(SortedListGetData(iter1)))->name, "pasha", "Prev");

	SortedListMerge(list_by_age, list_by_age2);

	VerifySizeT(SortedListSize(list_by_age), SortedListSize(list_by_age2) + 11,
				"Merge");

	SortedListMerge(list_by_age2, list_by_age);

	VerifySizeT(SortedListSize(list_by_age2), 11, "Merge");

	while (SortedListSize(list_by_age2) > 7)
	{
		SortedListPopFront(list_by_age2);
	}

	for (i = 7; i < 11; i++)
	{
		SortedListInsert(list_by_age, &students[i]);
	}

	SortedListMerge(list_by_age, list_by_age2);

	SortedListDestroy(list_by_age2);

	VerifyPointer(SortedListPopFront(list_by_age), &students[7], "Pop Front");
	VerifySizeT(SortedListSize(list_by_age), 10, "Pop Front");
	VerifyPointer(SortedListPopBack(list_by_age), &students[2], "Pop Back");
	VerifySizeT(SortedListSize(list_by_age), 9, "Pop Back");
	VerifyPointer(SortedListGetData(SortedListRemove(iter1)), &students[3], "Remove");

	{
		int param = 30;
		param = SortedListForEach(SortedListBegin(list_by_age),
		 							SortedListEnd(list_by_age),
									 &Operation, &param);

		VerifyInt(param, 1, "For Each");
	}
	
	
	VerifyInt(students[5].age, 30, "For Each");
	VerifyInt(students[0].age, 17, "For Each");
	VerifyInt(students[4].age, 35, "For Each");

	SortedListDestroy(list_by_age);

	for (i = 0; i < 11; i += 2)
	{
		SortedListInsert(list_by_name, &students[i]);
	}

	for (i = 1; i < 11; i += 2)
	{
		SortedListInsert(list_by_name2, &students[i]);
	}
	
	SortedListMerge(list_by_name, list_by_name2);

	for (i = 0; i < sizeof(students)/sizeof(students[0]); i++)
	{
		SortedListInsert(list_by_name2, &students[i]);
	}

	{
		int valid = 0;
		iter1 = SortedListPrev(SortedListEnd(list_by_name));
		iter2 = SortedListPrev(SortedListEnd(list_by_name2));
		for (i = 0; i < 11; i++)
		{
			valid += SortedListGetData(iter1) ==  SortedListGetData(iter2);
			iter1 = SortedListPrev(iter1);
			iter2 = SortedListPrev(iter2);
		}
		VerifyInt(valid, 11, "Merge");
	}

    SortedListDestroy(list_by_name);
	SortedListDestroy(list_by_name2);
   
}

/****************************************************************************/

int main()
{
    UgliestTestEver();       

    return 0;
}



