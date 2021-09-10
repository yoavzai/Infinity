#include <stdio.h>

typedef struct node node_t;

struct node
{
    int num;
    struct node* next;
};

void PrintList(node_t* head)
{
    while (head)
    {
        printf("%d ", head->num);
        head = head->next;
    }
    puts("");
}

node_t* Flip(node_t* head)
{
    node_t* next = head->next;
    node_t* tail = NULL;
    head->next = NULL;

    if (next == NULL)
    {
        return head;
    }

    tail = Flip(next);
    next->next = head;

    return tail;
}

int main()
{
    node_t node1;
    node_t node2;
    node_t node3;
    node1.num = 1;
    node1.next = &node2;
    node2.num = 2;
    node2.next = &node3;
    node3.num = 3;
    node3.next = NULL;

    PrintList(&node1);
    Flip(&node1);
    PrintList(&node1);
    PrintList(&node3);

    return 0;
}
