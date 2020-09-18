#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
  private:
    string str;
    int count;
    Node *left;
    Node *right;
    Node *parent;
    friend class BSTree;
  
  public:
    Node();
    Node(string str);
    string leftStr() const;
    int leftCount() const;
    string rightStr() const;
    int rightCount() const;
    bool hasleftOnly() const;
    bool hasrightOnly() const;
    bool hasChild() const;
};

#endif