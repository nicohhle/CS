#include "Node.h"
#include <iostream>
#include <string>

using namespace std;



Node::Node() {
    str = "";
    count = 0;
    left = 0;
    right = 0;
}
Node::Node(const string &s) {
    str = s;
    count = 1;
    left = 0;
    right = 0;
}

bool Node::hasChild() const {
    if (left || right) {
        return true;
    }
    
    return false;
}