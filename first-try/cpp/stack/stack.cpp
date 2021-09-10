#include "stack.hpp"
#include "deadbeef.hpp"

// add template <class DataType> to all funcs
// add <DataType> to all Stack

template <class DataType>
Stack<DataType>::Stack()
{}

template <class DataType>
Stack<DataType>::~Stack()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

template <class DataType>
void Stack<DataType>::Push(DataType data)
{
    m_dummy.m_next = new Node(data, m_dummy.m_next);
}

template <class DataType>
void Stack<DataType>::Pop()
{
    if (IsEmpty())
    {
        return;
    }

    Node* to_delete = m_dummy.m_next;
    m_dummy.m_next = m_dummy.m_next->m_next;

    delete to_delete;
}

template <class DataType>
DataType Stack<DataType>::Top() const
{
    if (IsEmpty())
    {
        // 3 //
        return DataType();
    }

    return m_dummy.m_next->GetData();
}

template <class DataType>
size_t Stack<DataType>::Count() const
{
    Node* cur_node = m_dummy.m_next;
    size_t counter = 0;

    while (cur_node != Deadbeef<Node>())
    {
        ++counter;
        cur_node = cur_node->m_next;
    }

    return counter; 
}

template <class DataType>
bool Stack<DataType>::IsEmpty() const
{
    return !m_dummy.HasNext();
}

// 4 change default Node constructor//
//template <class DataType>
//Stack<DataType>::Node::Node() : m_data(0), m_next(NULL)
//{}

template <class DataType>
Stack<DataType>::Node::Node(DataType data, Node* next) : m_data(data), m_next(next)
{}

template <class DataType>
DataType Stack<DataType>::Node::GetData() const
{
    return m_data;
}

template <class DataType>
// 5, add class after const //
const class Stack<DataType>::Node& Stack<DataType>::Node::GetNext() const
{
    return *m_next;
}

template <class DataType>
bool Stack<DataType>::Node::HasNext() const
{
    return m_next != Deadbeef<Node>();
}


