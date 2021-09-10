#include "SList.h"
#include "queue.h"
#include "test_functions.h"

void BestTestEver()
{
    int i = 0;
    int arr[] = {0,1,2};
    int arr2[] = {3,4,5};
    queue_t* my_queue = QCreate();
    queue_t* my_queue2 = QCreate();

    VerifyPointerNot(my_queue, NULL, "Create");
    VerifyPointer(QPeek(my_queue), NULL, "Peek");
    VerifySizeT(QSize(my_queue), 0, "Size");
    VerifyInt(QIsEmpty(my_queue), 1, "IsEmpty");

    for (i = 0; i < 3; ++i)
    {
        VerifyInt(QEnqueue(my_queue, &arr[i]), 0, "Enqueue");
        VerifyPointer(QPeek(my_queue), &arr[0], "Peek");
        VerifySizeT(QSize(my_queue), (size_t)(i + 1), "Size");
        VerifyInt(QIsEmpty(my_queue), 0, "IsEmpty");
    }

    for (i = 0; i < 2; ++i)
    {
        QDequeue(my_queue);
        VerifyPointer(QPeek(my_queue), &arr[i + 1], "Peek");
        VerifySizeT(QSize(my_queue), (size_t)(2 - i), "Size");
        VerifyInt(QIsEmpty(my_queue), 0, "IsEmpty");
    }
    
    QDequeue(my_queue);
    QDequeue(my_queue);
    VerifyInt(QIsEmpty(my_queue), 1, "Dequeue");

    QAppend(my_queue, my_queue2);
	VerifySizeT(QSize(my_queue), QSize(my_queue2), "Append");

    for (i = 0; i < 3; ++i)
    {
        QEnqueue(my_queue, &arr[i]);
    }

    QAppend(my_queue, my_queue2);
	VerifySizeT(QSize(my_queue), QSize(my_queue2) + 3, "Append");

    QAppend(my_queue2, my_queue);
	VerifyInt(QIsEmpty(my_queue2), 0, "Append");   

    for (i = 0; i < 3; ++i)
    {
        QEnqueue(my_queue, &arr2[i]);
    }

    QAppend(my_queue2, my_queue);
	VerifySizeT(QSize(my_queue2), 6, "Append");

	QDestroy(my_queue);
	QDestroy(my_queue2);	
}

int main()
{
    BestTestEver();
    
    return 0;
}

















