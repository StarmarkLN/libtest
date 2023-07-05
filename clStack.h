#pragma once
#include "Header.h"

template <class T>
class clStack {
private:
    vector<T> elems;      // elements 

public:
    void push(T const&);  // push element 
    void pop();           // pop element 
    T top() const;        // return top element 

    bool empty() const {  // return true if empty.
        return elems.empty();
    }
};

