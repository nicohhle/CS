#include <iostream>

using namespace std;

#include "Node.h"

Node::Node() {
    str = "";
    count = 0;
    left = 0;
    right = 0;
    parent = 0;
}

Node::Node(string str) {
    this->str = str;
    count = 1;
    left = 0;
    right = 0;
    parent = 0;
}

string Node::leftStr() const {
    return left->str;
}

int Node::leftCount() const {
    return left->count;
}

string Node::rightStr() const {
    return right->str;
}

int Node::rightCount() const {
    return right->count;
}

bool Node::hasChild() const {
    if (left != 0 || right != 0) {
        return true;
    } 
    
    return false;
}

bool Node::hasleftOnly() const {
    if (left != 0 && right == 0) {
        return true;
    }
    
    return false;
}

bool Node::hasrightOnly() const {
    if (left == 0 && right != 0) {
        return true;
    }
    
    return false;
}