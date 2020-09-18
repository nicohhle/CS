#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "Node.h"

#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {
  private:
    Node *root;

  public:
    AVLTree();
    int getHeight(Node *);
    void insert(const string &);
    int balanceFactor(Node *);
    void printBalanceFactors();
    void visualizeTree(const string &);

  private:
    Node * findUnbalancedNode(Node *);
    void insert (Node *, const string &);
    Node * findParent(Node *, Node *) const;
    void rotate(Node *);
    Node * rotateLeft(Node *);
    Node * rotateRight(Node *);
    void printBalanceFactors(Node *);
    void visualizeTree(ofstream &, Node *);

};

#endif