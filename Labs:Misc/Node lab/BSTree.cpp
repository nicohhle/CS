#include <iostream>
#include <string>

using namespace std;

#include "Node.h"
#include "BSTree.h"


BSTree::BSTree() {
    root = 0;
}

BSTree::~BSTree() {
    postDelete(root);
}

void BSTree::postDelete(Node *n) {
    if (n) {
        postDelete(n->left);
        postDelete(n->right);
        delete n;
    }
}

void BSTree::insert(const string &s) {
    if (root == 0) {
        root = new Node(s);
        return;
    } else if (search(s)) {
        increment(s);
        return;
    }
    
    Node *n = root;
    insert(n, s);
}

bool BSTree::search(const string &s) const {
    Node *empty = root;
    
    if (search(empty, s) == 0) {
        return false;
    }
    
    return true;
}

void BSTree::inOrder() const {
    if (root == 0) {
        cout << endl;
        return;
    } 
    
    inOrder(root);
    cout << endl;
}

void BSTree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void BSTree::preOrder() const {
    preOrder(root);
    cout << endl;
}

string BSTree::largest() const {
    if (root == 0) {
        return "";
    } else if (root->right == 0) {
        return root->str;
    }
    
    Node *curr = root;
    string currStr = curr->str;
    
    while (curr->right != 0) {
        currStr = curr->right->str;
        curr = curr->right;
    }
    
    return currStr;
}

string BSTree::smallest() const {
    if (root == 0) {
        return "";
    } else if (root->left == 0) {
        return root->str;
    }
    
    Node *curr = root;
    string currStr = curr->str;
    
    while (curr->left != 0) {
        currStr = curr->left->str;
        curr = curr->left;
    }
    
    return currStr;
}

int BSTree::height(const string &s) const {
    if (root == 0) {
        return -1;
    } else if (!search(s)) {
        return -1;
    }
    
    // Node *curr = root;
    // int lev = 0;
    
    // return height(s, curr, lev);
    
    Node *curr = search(root, s);
    return height(curr);
    
    // int h = 0;
    // Node *curr = root;
    
    // if (curr->str == s) {
    //     return h;
    // } else if (curr->str > s) {
    //     return height(curr->left->str) + 1;
    // } else {
    //     return height(curr->right->str) + 1;
    // }
}

int BSTree::height(Node *n) const {
    if (n) {
        if (!(n->hasChild())) {
            return 0;
        }
        
        int left = height(n->left) + 1;
        int right = height(n->right) + 1;
        
        if (left < right) {
            return right;
        } else {
            return left;
        }
    }
    
    // if (s == temp->str) {
    //     return h;
    // } else if (s < temp->str) {
    //     return height(s, temp->left, h + 1);
    // } else if (s > temp->str) {
    //     return height(s, temp->right, h + 1);
    // }
    
    return -1;
}

void BSTree::remove(const string &s) {
    if (!search(s)) {
        return;
    } 
    
    Node *curr = search(root, s);
    if (curr->count > 1) {
        curr->count--;
        return;
    }
    
    if (curr == root) {
        if (!(curr->hasChild())) {
            delete curr;
            root = 0; 
            return;
        }
    }
    
    remove(curr);
}

void BSTree::insert(Node *n, const string &s) {
    
    // Node *curr = n;
    
    // if (!(curr->hasChild())) {
    //     if (curr->str > s) {
    //         curr->left = new Node(s);
    //         return;
    //     } else {
    //         curr->right = new Node(s);
    //         return;
    //     }
    // } else {
    //     if (curr->str > s) {
    //         insert(curr->left, s);
    //     } else {
    //         insert(curr->right, s);
    //     }
    // }
    
    if (s < n->str) {
        if (n->left == 0) {
            n->left = new Node(s);
            n->left->parent = n;
            return;
        } else {
            return insert(n->left, s);
        }
    } else if (s > n->str) {
        if (n->right == 0) {
            n->right = new Node(s);
            n->right->parent = n;
            return;
        } else {
            return insert(n->right, s);
        }
    }
    
    // Node *curr = root;
    // if (root == 0) {
    //     root = n;
    // } else {
    //     while (curr->hasChild()) {
    //         if (n->str > s) {
    //             insert(n->left, s);
    //         } else {
    //             insert(n->right, s);
    //         }
    //     }
    // }
    
    // if (n->str > s) {
    //     n->left = new Node(s, c++);
    // } else {
    //     n->right = new Node(s, c++);
    // }
    
    // } else if (s < n->str) {
    //     n->left = insert(node->left, s);
    // } else {
    //     n->right = insert(node->right, s);
    // }
}

void BSTree::increment(string s) {
    Node *n = root;
    Node *temp = search(n, s);
    temp->count = (temp->count) + 1;
}

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

Node * BSTree::search(Node *n, const string &s) const {
    if (n == 0) {
        return 0;
    } else if (s == n->str) {
        return n;
    } else if (s < n->str) {
        return search(n->left, s);
    } else {
        return search(n->right, s);
    }
}

Node * BSTree::getParent(Node *n, Node *beg) {
    if (beg) {
        if (beg->left == n) {
            return beg;
        }
        
        if (beg->right == n) {
            return beg;
        }
        
        if (n->str < beg->str) {
            return getParent(n, beg->left);
        } else {
            return getParent(n, beg->right);
        }
    }
    
    return beg;
}

Node *BSTree::largest(Node *n) {
    if (n) {
        if (n->right == 0) {
            return n;
        } 
        return largest(n->right);
    }
    
    return 0;
}

Node *BSTree::smallest(Node *n) {
    if (n) {
        if (n->left == 0) {
            return n;
        }
        
        return smallest(n->left);
    }
    
    return 0;
}

void BSTree::remove(Node *n) {
    // // Item not found
    // if (!search(s)) {
    //     return;
    // }
    
    // Node *parent = getParent(n, root);
    
    if (!(n->hasChild())) {
        if (n->parent->left == n) {
            n->parent->left = 0;
        } else {
            n->parent->right = 0;
        }
        
        delete n;
        return;
    } else {
        if (n->left) {
            Node *curr = largest(n->left);
            n->str = curr->str;
            n->count = curr->count;
            remove(curr);
        } else if (n->right) {
            Node *currr = smallest(n->right);
            n->str = currr->str;
            n->count = currr->count;
            remove(currr);
        }
    }
    
    // // Removing a leaf
    // if (!(n->left->hasChild()) && s == n->left->str) {
    //     Node *curr = n->left;
    //     delete curr;
    //     n->left = 0;
    // } else if (!(n->right->hasChild()) && s == n->left->str) {
    //     Node *curr = n->right;
    //     delete curr;
    //     n->right = 0;
    // } else {
    //     if (s < n->str) {
    //         remove(n->left, s);
    //     } else {
    //         remove(n->right, s);
    //     }
    // }
    
    // // Removing a node w 1 child - right only
    // if (s == n->left->str && n->left->hasrightOnly()) {
    //     Node *curr = n->left;
    //     n->left = n->left->right;
    //     delete curr;
    // } else if (s == n->right->str && n->right->hasrightOnly()) {
    //     Node *curr = n->right;
    //     n->right = n->right->right;
    //     delete curr;
    // } else {
    //     if (s < n->str) {
    //         remove(n->left, s);
    //     } else {
    //         remove(n->right, s);
    //     }
    // }
    
    // // Removing a node w 1 child - left only
    // if (s == n->left->str && n->left->hasleftOnly()) {
    //     Node *curr = n->left;
    //     n->left = n->left->left;
    //     delete curr;
    // } else if (s == n->right->str && n->right->hasleftOnly()) {
    //     Node *curr = n->right;
    //     n->right = n->right->left;
    //     delete curr;
    // } else {
    //     if (s < n->str) {
    //         remove(n->left, s);
    //     } else {
    //         remove(n->right, s);
    //     }
    // }
    
    // // Removing a node w 2 children
}