#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void Delete(Node *);
  
  void preOrder(Node *) const;
  void inOrder(Node *) const;
  void postOrder(Node *) const;
  
  void insert(Node *, Node *, const string &);
  
  void split(Node *, Node *, Node *, Node *, const string &);
  void set(Node *, Node * &, string &, const string &);
  
  void remove(Node *, const string &);
  Node *inorderSucc(Node *);
  void fix(Node *, Node *);
  void merge(Node *, Node *);
  void redistribute(Node *, Node *);
  
  void search(Node *, const string &, string &) const;
};

#endif
