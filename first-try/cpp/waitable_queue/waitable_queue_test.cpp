#include <iostream>
#include <queue>
#include <pthread.h>

#include "waitable_queue.hpp"

using std::cout;
using std::endl;
using namespace ilrd;

WaitableQueue< std::queue<int> > pq;
int outarr[10];

void* Producer(void* num)
{
    int i = 0;
    (void)num;

    for (i = 0; i < 10; ++i)
    {
        pq.Push(i);
        sleep(1);
    }

    return NULL;
}

void* Consumer(void* param)
{
    pq.Pop(outarr[*(int*)param], 11);

    return NULL;
}

int main()
{
    int i = 0;
    int nums[] = {0,1,2,3,4,5,6,7,8,9};
    pthread_t producer;
    pthread_t consumers[10];

    pthread_create(&producer, NULL, Producer, NULL);

    for (i = 0; i < 10; ++i)
    {
        pthread_create(&consumers[i], NULL, Consumer, &nums[i]);
    }

    pthread_join(producer, NULL);

    for (i = 0; i < 10; ++i)
    {
        pthread_join(consumers[i], NULL);
    }

    for (i = 0; i < 10; ++i)
    {
        cout << outarr[i] << endl;
    }

    return 0;
}












