#include <iostream>

using namespace std;

#include "IntList.h"

int main() {
    IntList test;
    
    if (test.empty()) {
        cout << "List is empty." << endl;
    } 
    else {
        cout << "List is not empty." << endl;
    }
    
    cout << endl;
    
    cout << "Testing push back." << endl;
    test.push_back(1);
    test.push_back(8);
    test.push_back(3);
    test.printReverse();
    cout << endl;
    
    cout << "Testing pop back." << endl;
    test.pop_back();
    test.printReverse();
    cout << endl;
    
    if (test.empty()) {
        cout << "List is empty." << endl;
    } 
    else {
        cout << "List is not empty." << endl;
    }
    
    cout << "Testing push front." << endl;
    test.push_front(7);
    test.push_front(10);
    test.printReverse();
    cout << endl;
    
    cout << "Testing pop front." << endl;
    test.pop_front();
    test.printReverse();
    cout << endl;
    
    
    while (!test.empty()) {
        test.pop_front();
    }
    test.printReverse();
    cout << endl;
    
    
    if (test.empty()) {
        cout << "List is empty." << endl;
    } else {
        cout << "List is not empty." << endl;
    }
    
    
    return 0;
}
    
    