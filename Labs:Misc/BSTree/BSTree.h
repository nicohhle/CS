#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"

using namespace std;

class BSTree {

private:
  Node *root;

private:
  void Delete(Node *);
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  void preOrder(Node *) const;
  Node * largest(Node *) const;
  Node * smallest(Node *) const;
  int height(Node *) const;
  Node * findParent(Node *, Node *) const;
  Node * search(Node *, const string &) const;
  void insert(Node *, const string &); 
  void remove(Node *);

public:
  BSTree();
  ~BSTree();
  void insert(const string &);
  bool search(const string &) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void preOrder( ) const;
  string largest( ) const;
  string smallest( ) const;
  int height(const string &) const;
  void remove(const string &);
};

#endif