#include <iostream>
#include <string>

using namespace std;

#include "Node.h"

Node::Node() {
    small = "";
    large = "";
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
}

Node::Node(const string &s) {
    small = s;
    large = "";
    left = 0;
    middle = 0;
    right = 0;
    parent = 0;
}
