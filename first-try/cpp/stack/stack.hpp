#ifndef _STACK_
#define _STACK_

#include <stdlib.h> // size_t

#include "deadbeef.hpp"

// 1
//typedef int DataType;

// 2
template <class DataType>
struct Stack
{
    public:
    explicit Stack();
    ~Stack();

    void Push(DataType data);
    void Pop();
    DataType Top() const;
    size_t Count() const;
    bool IsEmpty() const;

    struct Node
    {
        //explicit Node();
        explicit Node(DataType data = DataType(), Node* next = Deadbeef<Node>());

        DataType GetData() const;
        bool HasNext() const;
        const Node& GetNext() const;

        DataType m_data;
        Node* m_next;
    };
    
    Node m_dummy;
};

#include "stack.cpp"

#endif