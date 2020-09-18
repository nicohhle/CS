#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"

using namespace std;

class BSTree {

  private:
    Node *root;

  private:
    void insert(Node *, const string &);
    void inOrder(Node *) const;
    void postOrder(Node *) const;
    void preOrder(Node *) const;
    Node *search(Node *, const string &) const;
    void remove(Node *);
    void increment(string);
    int height(Node *) const;
    Node *getParent(Node *, Node *);
    Node *largest(Node *);
    Node *smallest(Node *);
    void postDelete(Node *n);

  public:
    BSTree();
    ~BSTree();
    void insert(const string &);
    bool search(const string &) const;
    void inOrder() const;
    void postOrder() const;
    void preOrder() const;
    string largest() const;
    string smallest() const;
    int height(const string &) const;
    void remove(const string &);
    
};

#endif