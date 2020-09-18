
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <string>

using namespace std;



class Node {
  friend class BSTree;
  private:
    string str;
    int count;
    Node *left;
    Node *right;
    
  public:
    Node();
    Node(const string &);
    bool hasChild() const;
};

#endif