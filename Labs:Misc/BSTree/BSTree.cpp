#include <iostream>
#include <string>

#include "Node.h"
#include "BSTree.h"

using namespace std;

BSTree::BSTree() {
    root = 0;
}

BSTree::~BSTree() {
    Delete(root);
}

void BSTree::Delete(Node *n) {
    if (n) {
        Delete(n->left);
        Delete(n->right);
        delete n;
    }
}

// IN/POST/PRE-ORDER ---------------------------------------------------------------
void BSTree::inOrder(Node *n) const {
    if (n) {
        inOrder(n->left);
        cout << n->str << "(" << n->count << "), ";
        inOrder(n->right);
    }
}
void BSTree::postOrder(Node *n) const {
    if (n) {
        postOrder(n->left);
        postOrder(n->right);
        cout << n->str << "(" << n->count << "), ";
    }
}
void BSTree::preOrder(Node *n) const {
    if (n) {
        cout << n->str << "(" << n->count << "), ";
        preOrder(n->left);
        preOrder(n->right);
    }
}
  
void BSTree::inOrder( ) const {
    inOrder(root);
    cout << endl;
}

void BSTree::postOrder( ) const {
    postOrder(root);
    cout << endl;
}

void BSTree::preOrder( ) const {
    preOrder(root);
    cout << endl;
}

// LARGEST FUNCTIONS ---------------------------------------------------------------

string BSTree::largest( ) const {
    if (root == 0) {
        return "";
    }
    
    Node *curr = root;
    
    if (curr) {
        while (curr->right) {
            curr = curr->right;
        }
    }    
    
    return curr->str;
}

Node * BSTree::largest(Node *n) const {
    while (n->right) {
            n = n->right;
        }
    
    return n;
}

// SMALLEST FUNCTIONS ---------------------------------------------------------------

string BSTree::smallest( ) const {
    if (root == 0) {
        return "";
    }
    
    Node *curr = root;
    
    if (curr) {
        while (curr->left) {
            curr = curr->left;
        }
    }
    
    return curr->str;
}

Node * BSTree::smallest(Node *n) const {
    while (n->left) {
            n = n->left;
        }
    
    return n;
}

// HEIGHT FUNCTION ---------------------------------------------------------------

int BSTree::height(const string &s) const {
    if (!root || !search(s)) {
        return -1;
    }
    
    Node *curr = search(root, s);
    return height(curr);
}

int BSTree::height(Node *n) const {
    if (n) {
        if (!n->hasChild()) {
            return 0;
        }
        
        int r = height(n->right) + 1;
        int l = height(n->left) + 1;
        
        if (l < r) {
            return r;
        } 
        else {
            return l;
        }
    }
    
    return -1;
}
    
// FIND PARENT FUNCTION ---------------------------------------------------------------

Node * BSTree::findParent(Node *n, Node *start) const {
    Node *curr = start;
        
    if (curr->right == n || curr->left == n) {
        return curr;
    } 
    else {
        if (curr->str < n->str) {
            return findParent(n, curr->right);
        } 
        else {
            return findParent(n, curr->left);
        }
    }
    
    return curr;
}

// INSERT FUNCTIONS ---------------------------------------------------------------

void BSTree::insert(const string &s) {
    if (!root) {
        root = new Node(s);
        return;
    } 
    else if (search(s)) {
        Node *temp = search(root, s);
        temp->count = temp->count + 1;
        return;
    } 
    else {
        Node *curr = root;
        insert(curr, s);
    }
}

void BSTree::insert(Node *n, const string &s) {
    if (n->str < s) {
        if (!n->right) {
            n->right = new Node(s);
            return;
        } 
        else {
            insert(n->right, s);
        }
    } 
    else if (n->str > s) {
        if (!n->left) {
            n->left = new Node(s);
            return;
        } 
        else {
            insert(n->left, s);
        }
    }
}

// SEARCH FUNCTIONS ---------------------------------------------------------------

bool BSTree::search(const string &s) const {
    if (search(root, s) != 0) {
        return true;
    }
    
    return false;
}

Node * BSTree::search(Node *curr, const string &s) const {
    if (curr) {
        if (curr->str == s) {
            return curr;
        } 
        else if (s < curr->str) {
            return search(curr->left, s);
        } 
        else {
            return search(curr->right, s);
        }
    }
    
    return 0;
}

// REMOVE FUNCTIONS ---------------------------------------------------------------

void BSTree::remove(const string &s) {
    if (!root || !search(s)) {
        return;
    }
    
    Node *curr = search(root, s);
    if (curr->count > 1) {
        curr->count--;
        return;
    }
    
    if (curr == root) {
        if (!curr->hasChild()) {
            delete curr;
            root = 0;
            return;
        }
    }
    
    remove(curr);
}

void BSTree::remove(Node *n) {
    if (!n->hasChild()) {
        Node *temp = findParent(n, root);
        
        if (temp->right == n) {
            temp->right = 0;
        }
        else if (temp->left == n) {
            temp->left = 0;
        }
        
        delete n;
        temp = 0;
        return;
    }
    else {
        if (n->left) {
            Node *curr = largest(n->left);
            n->str = curr->str;
            n->count = curr->count;
            remove(curr);
            return;
        }
        
        else if (n->right) {
            Node *currr = smallest(n->right);
            n->str = currr->str;
            n->count = currr->count;
            remove(currr);
        }
    }
}
