#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string &s) {
  root = 0;
  infixExpression = s;
}

/* Implementation of destrucor is optional.
   The destructor should deallocate all the nodes in the tree. */
// arithmeticExpression::~arithmeticExpression();

void arithmeticExpression::buildTree() {
  string postfix = infix_to_postfix();
  char ch = 'a';

  stack<TreeNode *> s;

  for (unsigned i = 0; i < postfix.size(); ++i) {
    TreeNode *t = new TreeNode(postfix.at(i), ch++);

    if (postfix.at(i) == '+' || postfix.at(i) == '-' || postfix.at(i) == '*' || postfix.at(i) == '/') {
      t->right = s.top();
      s.pop();
      t->left = s.top();
      s.pop();

      s.push(t);

    } else {
      s.push(t);
    }
  }

  // at end when s only has root left in stack
  root = s.top();
}

// HELPER FUNCTIONS ----------------------------------------------------------------------------------------------------

int arithmeticExpression::priority(char op) {
  int priority = 0;
  if (op == '(') {
    priority = 3;
  } else if (op == '*' || op == '/') {
    priority = 2;
  } else if (op == '+' || op == '-') {
    priority = 1;
  }
  return priority;
}

string arithmeticExpression::infix_to_postfix() {
  stack<char> s;
  ostringstream oss;
  char c;
  for (unsigned i = 0; i < infixExpression.size(); ++i) {
    c = infixExpression.at(i);
    if (c == ' ') {
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {  //c is an operator
      if (c == '(') {
        s.push(c);
      } else if (c == ')') {
        while (s.top() != '(') {
          oss << s.top();
          s.pop();
        }
        s.pop();
      } else {
        while (!s.empty() && priority(c) <= priority(s.top())) {
          if (s.top() == '(') {
            break;
          }
          oss << s.top();
          s.pop();
        }
        s.push(c);
      }
    } else {  //c is an operand
      oss << c;
    }
  }
  while (!s.empty()) {
    oss << s.top();
    s.pop();
  }
  return oss.str();
}

// INFIX / PREFIX / POSTFIX ----------------------------------------------------------------------------------------------------

void arithmeticExpression::infix(TreeNode *t) {
  if (t) {
    if (t->left) {
      cout << "(";
    }
    // cout << "hey-";
    infix(t->left);
    cout << t->data;
    infix(t->right);

    if (t->right) {
      cout << ")";
    }
  }
}

void arithmeticExpression::prefix(TreeNode *t) {
  if (t) {
    // cout << "t_";
    cout << t->data;
    prefix(t->left);
    prefix(t->right);
  }
}

void arithmeticExpression::postfix(TreeNode *t) {
  if (t) {
    postfix(t->left);
    postfix(t->right);
    cout << t->data;
    // cout << "data=";
  }
}

void arithmeticExpression::infix() {
  infix(root);
}

void arithmeticExpression::prefix() {
  prefix(root);
}

void arithmeticExpression::postfix() {
  postfix(root);
}

// VISUALIZE TREE ----------------------------------------------------------------------------------------------------

void arithmeticExpression::visualizeTree(const string &outputFilename) {
  ofstream outFS(outputFilename.c_str());
  if (!outFS.is_open()) {
    cout << "Error opening " << outputFilename << endl;
    return;
  }
  outFS << "digraph G {" << endl;
  visualizeTree(outFS, root);
  outFS << "}";
  outFS.close();
  string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
  string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
  system(command.c_str());
}

void arithmeticExpression::visualizeTree(ofstream &out, TreeNode *t) {
  // format graph by using digraph G3
  out << t->key << "[label=\"" << t->data << "\"];";

  if (t) {
    if (t->left) {
      out << t->key << "->" << t->left->key << ";";
      visualizeTree(out, t->left);
    }

    if (t->right) {
      out << t->key << "->" << t->right->key << ";";
      visualizeTree(out, t->right);
    }
  }
}