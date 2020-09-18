#include <iostream>

using namespace std;

#include "IntVector.h"

int main() {
    IntVector test;
    IntVector *temp;
    int size = 5;
    int capacity;
    
    test = IntVector();
    test = IntVector(size);
    
    temp = new IntVector;
    delete temp;
    
    cout << "Testing size." << endl;
    size = test.size();
    if (size == 5) {
        cout << "Size test worked. Size: " << size << endl;
    } else {
        cout << "Size test did not work. FIX size function" << endl;
    }
    
    cout << endl;
    
    cout << "Testing capacity." << endl;
    capacity = test.capacity();
    if (capacity == 5) {
        cout << "Capacity test worked. Capacity: " << capacity << endl;
    } else {
        cout << "Capacity test did not work. FIX capacity function" << endl;
    }
    
    cout << endl;
    
    cout << "Checking if vector is empty." << endl;
    bool isEmpty = test.empty();
    if (isEmpty) {
        cout << "Empty test result: is empty" << endl;
    } else {
        cout << "Empty test result: is not empty" << endl;
    }
    
    cout << endl;
    
    cout << "For now, " << endl;
    cout << "At 2nd index, value is: " << test.at(2) << endl;
    cout << "During this time, value at front is: " << test.front() << endl;
    cout << "During this time, value at back is: " << test.back() << endl;
    cout << "At this point, size is: " << test.size() << endl;
    cout << "At this point, capacity is: " << test.capacity() << endl;
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Inserting value 3 at index 2." << endl;
    test.insert(2, 3);
    
    cout << "Now, at 2nd index, value is: " << test.at(2) << endl;
    cout << "Now, value at front is: " << test.front() << endl;
    cout << "Now, value, at back is: " << test.back() << endl;
    cout << "The current size is: " << test.size() << endl;
    cout << "The current capacity is: " << test.capacity() << endl;
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Now inserting value 4 at the end." << endl;
    test.insert(test.size(), 4);
    cout << "Value at back is now: " << test.back() << endl;
    cout << "Size is now: " << test.size() << endl;
    cout << "Capacity is: " << test.capacity() << endl;
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Erasing value at index 1." << endl;
    test.erase(1);
    
    cout << "Now, at 2nd index, value is: " << test.at(2) << endl;
    cout << "Now, value at front is: " << test.front() << endl;
    cout << "Now, value, at back is: " << test.back() << endl;
    cout << "Size is now: " << test.size() << endl;
    cout << "Capacity is: " << test.capacity() << endl;
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Resizing to 8 and filling values with 7." << endl;
    test.assign(8, 7);
    
    cout << "Now, at 2nd index, value is: " << test.at(2) << endl;
    cout << "Now, value at front is: " << test.front() << endl;
    cout << "Now, value, at back is: " << test.back() << endl;
    
    cout << endl;
    
    cout << "At this point, size is: " << test.size() << endl;
    cout << "At this point, capacity is: " << test.capacity() << endl;
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    int size1 = test.size();
    
    cout << "Pushing back value 5." << endl;
    test.push_back(5);
    
    if (test.back() == 5) {
        cout << "Push back 5 test worked. Value at back is now: " << test.back() << endl;
    } else {
        cout << "Push back test did not work. FIX push back function" << endl;
    }
    
    // int size1 = test.size();
    size = test.size();
    if (size == size1 + 1) {
        cout << "Now, size has increased by 1. Size is: " << test.size() << endl;
        cout << "Capacity is: " << test.capacity() << endl;
    } 
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Test decreasing size by 1. Size before: " << test.size() << endl;
    size1 = test.size();
    test.pop_back();
    size = test.size();
    cout << "Size now: " << test.size() << endl;
    if (size == size1 - 1) {
        cout << "Pop back test worked. Size has decreased by 1" << endl; 
    } else {
        cout << "Pop back test did not work. FIX pop back function" << endl;
    }
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Clearing vector." << endl;
    test.clear();
    if (test.size() == 0) {
        cout << "Test to clear worked. Size is now 0" << endl;
    } else {
        cout << "Test to clear did not work. FIX clear function" << endl;
    }
    
    cout << endl;
    
    cout << "Resizing vector to 4." << endl;
    test.resize(4);
    if (test.size() == 4) {
        cout << "Resizing test worked. Size is now: " << test.size() << endl;
    } else {
        cout << "Resizing test did not work. FIX resize function" << endl;
    }
    
    cout << endl;
    
    cout << "The full vector shown: {";
    
    for (int i = 0; i < test.size() - 1; ++i) {
        cout << test.at(i) << ", ";
    }
    
    cout << test.at(test.size() - 1) << "}" << endl;
    
    cout << endl;
    
    cout << "Reserving 18 as minimum for capacity." << endl;
    test.reserve(18);
    cout << "Size unchanged. Capacity is now: " << test.capacity() << endl;
    
    return 0;
}