#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

Node::Node() {
    str = "";
    left = 0;
    right = 0;
}
Node::Node(const string &s) {
    str = s;
    left = 0;
    right = 0;
}

bool Node::hasChild() const {
    if (left || right) {
        return true;
    }
    
    return false;
}