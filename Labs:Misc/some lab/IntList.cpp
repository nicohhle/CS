#include <iostream>

using namespace std;

#include "IntList.h"

IntList::IntList() {
    dummyHead = 0;
    dummyTail = 0;
} 
//: Initializes an empty list with dummy head and dummy tail.

IntList::~IntList() {
    IntNode *curr = dummyHead;
    
    while (curr != 0) {
        curr = curr -> next;
        delete dummyHead;
        dummyHead = curr;
    }
}
//: Deallocates all remaining dynamically allocated memory (all remaining IntNodes).

void IntList::push_front(int value) {
    IntNode *push = new IntNode(value);
    
    if (dummyHead == 0) {
        dummyHead = push;
        dummyTail = push;
        return;
    }
    
    push->next = dummyHead;
    dummyHead->prev = push;
    dummyHead = push;
}
//: Inserts a data value (within a new node) at the front end of the list. This must be an O(1) operation.

void IntList::pop_front() {
    IntNode *curr = 0;
    
    if (dummyHead != 0) {
        if (dummyHead == dummyTail) {
            dummyTail = 0;
            delete dummyHead;
            dummyHead = 0;
        }
        else {
            curr = dummyHead -> next;
            curr -> prev = 0;
            delete dummyHead;
            dummyHead = curr;
        }
    }

}
//: Removes the node at the front end of the list (the node after the dummy head). Does nothing if the list is already empty. This must be an O(1) operation.

void IntList::push_back(int value) {
    IntNode *push = new IntNode(value);
    
    if (dummyHead == 0 && dummyTail == 0) {
        dummyHead = push;
        dummyTail = push;
    } 
    else {
        dummyTail->next = push;
        push->prev = dummyTail;
        dummyTail = push;
    }
} 
//: Inserts a data value (within a new node) at the back end of the list. This must be an O(1) operation.

void IntList::pop_back() {
    if (dummyHead != 0) {
        if (dummyHead == dummyTail) {
            dummyHead = 0;
            delete dummyTail;
            dummyTail = 0;
        }
        else {
            IntNode *pop = dummyTail;
            
            dummyTail = dummyTail->prev;
            dummyTail->next = 0;
            
            delete pop;
        }
    }
}
//: Removes the node at the back end of the list (the node before the dummy tail). Does nothing if the list is already empty. This must be an O(1) operation.

bool IntList::empty() const {
    if (dummyHead == 0 && dummyTail == 0) {
        return true;
    }
    else {
        return false;
    }
}
//: Returns true if the list does not store any data values (it only has dummy head and dummy tail), otherwise returns false.

ostream & operator<<(ostream &out, const IntList &rhs) {
    IntNode *curr = rhs.dummyHead;
    
    while (curr != 0) {
        out << curr->data;
        
        if (curr->next != 0) {
            out << " ";
        }
        
        curr = curr->next;
    }
    
    return out;
}
//: A global friend function that outputs to the stream all of the integer values within the list on a single line, 
//each separated by a space. This function does NOT send to the stream a newline or space at the end.

void IntList::printReverse() const {
    for (IntNode *i = dummyTail; i != 0; i = i -> prev) {
        if (i->prev != 0) {
            cout << i -> data << " ";
        }
        else {
            cout << i -> data;
        }
    }
}
//: prints to a single line all of the int values stored in the list in REVERSE order, each separated by a space. 
//This function does NOT output a newline or space at the end.