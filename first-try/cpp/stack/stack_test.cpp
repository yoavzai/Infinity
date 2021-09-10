#include <stdio.h>
#include <iostream>

#include "string.hpp"
#include "stack.hpp"

using namespace ilrd;

int main()
{
    //String* arr = new String[5];
    //arr[0] = "zero";
    //arr[1] = "one";
    //arr[2] = "two";
    //arr[3] = "three";
    //arr[4] = "four";
    
    Stack<double> stack;
    //Stack<String> str_stack;

    std::cout << stack.IsEmpty() << " =? 1" << std::endl;
    std::cout << stack.Count() << " =? 0" << std::endl;
    std::cout << stack.Top() << " =? 0" << std::endl;

    stack.Pop();

    double i = 0;

    for (i = 0; i < 5; i += 0.5)
    {
        stack.Push(i);
        std::cout << "Pushed " << i << std::endl;
    }

    std::cout << stack.IsEmpty() << " =? 0" << std::endl;
    std::cout << stack.Count() << " =? 10" << std::endl;
    std::cout << stack.Top() << " =? 4.5" << std::endl;

    for (i = 0; i < 5; i += 0.5)
    {
        std::cout << "Popping " << stack.Top() << std::endl;
        stack.Pop();
    }

    std::cout << stack.IsEmpty() << " =? 1" << std::endl;
    std::cout << stack.Count() << " =? 0" << std::endl;
    std::cout << stack.Top() << " =? 0" << std::endl;

    return 0;
}