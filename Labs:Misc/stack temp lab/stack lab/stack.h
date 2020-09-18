/#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

#ifndef STACK_H
#define STACK_H

const int MAX_SIZE = 20;

template <typename T>
class stack {
  private:
    T data[MAX_SIZE];
    int size;
    
  public:
    stack() { 
        size = 0; 
    }
    void push(T val) {
        if (size == MAX_SIZE) {
            throw overflow_error("Called push on full stack.");
        }
        
        data[size] = val;
        size++;
    }
    void pop() {
        if (empty()) {
            throw out_of_range("Called pop on empty stack.");
        } 
        
        size--;
    }
    T top() { 
        if (empty()) {
            throw underflow_error("Called top on empty stack.");
        } 
        
        return data[size - 1];
    }
    bool empty() { 
        if (size == 0) { 
            return true; 
        }
        
        return false;
    }
};

#endif
