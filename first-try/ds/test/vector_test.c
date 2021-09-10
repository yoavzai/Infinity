#include <stdio.h>

#include "vector.h"
#include "test_functions.h"

void TestCreate()
{
    vector_t* my_vector = VectorCreate(0, 2);
    VerifyPointer(my_vector, NULL, "Create");
    VectorDestroy(my_vector);
    my_vector = VectorCreate(2, 0);
    VerifyPointer(my_vector, NULL, "Create");
    VectorDestroy(my_vector);
    my_vector = VectorCreate(sizeof(int), 2);
    VerifyPointerNot(my_vector, NULL, "Create");
    VectorDestroy(my_vector);
    my_vector = VectorCreate(sizeof(int), ~0UL);
    VerifyPointer(my_vector, NULL, "Create");
    VectorDestroy(my_vector);
}

void TestSize()
{
    int num1 = 1;
    vector_t* my_vector = VectorCreate(sizeof(int), 2);

    VerifySizeT(VectorSize(my_vector), 0, "Size");
    VectorPushBack(my_vector, &num1);
    VerifySizeT(VectorSize(my_vector), 1, "Size");
    VectorDestroy(my_vector);
    VerifySizeT(VectorSize(my_vector), 0, "Size");
}

void TestCapacity()
{
    int num1 = 1;
    vector_t* my_vector = VectorCreate(sizeof(int), 2);

    VerifySizeT(VectorCapacity(my_vector), 2, "Capacity");
    VectorPushBack(my_vector, &num1);
    VerifySizeT(VectorCapacity(my_vector), 2, "Capacity");
    VectorPushBack(my_vector, &num1);
    VectorPushBack(my_vector, &num1);
    VerifySizeT(VectorCapacity(my_vector), 4, "Capacity");
    VectorPopBack(my_vector);
    VectorPopBack(my_vector);
    VectorPopBack(my_vector);
    VerifySizeT(VectorCapacity(my_vector), 2, "Capacity");
    VectorDestroy(my_vector);
    VerifySizeT(VectorCapacity(my_vector), 0, "Capacity");
}

void TestPushBack()
{
    int num1 = 1;
    vector_t* my_vector = VectorCreate(sizeof(int), 2);

    VerifyInt(VectorPushBack(my_vector, &num1), 0, "PushBack");
    VectorDestroy(my_vector);
    VerifyInt(VectorPushBack(my_vector, &num1), -1, "PushBack");
}

void TestPopBack()
{
    int num1 = 1;
    vector_t* my_vector = VectorCreate(sizeof(int), 2);
    
    VectorPopBack(my_vector);
    VectorDestroy(my_vector);
    VectorPopBack((vector_t*)&num1);
}

void TestGetItemAddress()
{
    int num1 = 1;
    int num2 = 2;
    vector_t* my_vector = VectorCreate(sizeof(int), 2);
    
    VerifyPointer(VectorGetItemAddress(my_vector, 0), NULL, "GetItemAddress");
    VerifyPointer(VectorGetItemAddress((const vector_t *)&num1, 1), NULL, "GetItemAddress");
    VerifyPointer(VectorGetItemAddress(my_vector, 1), NULL, "GetItemAddress");
    VectorPushBack(my_vector, &num1);
    VectorPushBack(my_vector, &num2);
    VerifyInt(*((int*)(VectorGetItemAddress(my_vector, 1))), 2, "GetItemAddress");

    VerifyInt(*((int*)(VectorGetItemAddress(my_vector, 0))), 1, "GetItemAddress");
    VectorDestroy(my_vector);
  
}

void TestReserve()
{
    int num = 1;
    vector_t* my_vector = VectorCreate(sizeof(int), 2);
    
    VerifyInt(VectorReserve(my_vector, 20), 0, "Reserve");
    VectorPushBack(my_vector, &num);
    VerifyInt(VectorReserve(my_vector, ~0UL), 1, "Reserve");
    VerifyInt(*((int*)(VectorGetItemAddress(my_vector, 0))), 1, "Reserve");
    VectorDestroy(my_vector);
    VerifyInt(VectorReserve(my_vector, 1), -1, "Reserve");
}

void TestInvalid()
{
    int num = 1;
    VectorDestroy((vector_t*)&num);
    VectorPopBack((vector_t*)&num);
}

int main()
{
    TestCreate();
    TestSize();
    TestCapacity();
    TestPushBack();
    TestPopBack();
    TestGetItemAddress();
    TestReserve();
    TestInvalid();

    return 0;
}




