#include "clStack.h"

template <class T>
void clStack<T>::push(T const& elem) 
{
    elems.push_back(elem);
}

template <class T>
void clStack<T>::pop() 
{
    if (elems.empty()) 
    {
        throw out_of_range("Stack<>::pop(): empty stack");
    }

    elems.pop_back();
}

template <class T>
T clStack<T>::top() const 
{
    if (elems.empty()) 
    {
        throw out_of_range("Stack<>::top(): empty stack");
    }

    return elems.back();
}

/* First method  */
/*
template class Stack<int>;
template class Stack<double>;
template class Stack<string>;
*/
