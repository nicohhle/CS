#include <iostream>
#include <string>
#include <queue>

using namespace std;

#include "Node.h"
#include "Tree.h"

Tree::Tree() {
    root = 0;
}

Tree::~Tree() {
    Delete(root);
    root = 0;
}

void Tree::Delete(Node *n) {
    if (n) {
        Delete(n->left);
        Delete(n->middle);
        Delete(n->right);
        
        delete n;
    }
}

// ========================================================================================================
// ORDERING - IN/PRE/POST ----------------------------------------------------------------------------------------
// ========================================================================================================

void Tree::preOrder() const {
    preOrder(root);
    cout << endl;
}

void Tree::inOrder() const {
    inOrder(root);
    cout << endl;
}

void Tree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void Tree::preOrder(Node *n) const {
    if (n) {
        cout << n->small << ", ";
        preOrder(n->left);
        if (n->large != "") {
            cout << n->large << ", ";
        }
        preOrder(n->middle);
        preOrder(n->right);
    }
}

void Tree::inOrder(Node *n) const {
    if (n) {
        inOrder(n->left);
        cout << n->small << ", ";
        inOrder(n->middle);
        if (n->large != "") {
            cout << n->large << ", ";
        }
        inOrder(n->right);
    }
}

void Tree::postOrder(Node *n) const {
    if (n) {
        postOrder(n->left);
        postOrder(n->middle);
        cout << n->small << ", ";
        postOrder(n->right);
        if (n->large != "") {
            cout << n->large << ", ";
        }
    }
}

// ========================================================================================================
// INSERTION ----------------------------------------------------------------------------------------
// ========================================================================================================

void Tree::insert(const string &s) {
    if (!root) {
        root = new Node();
        root->small = s;
    }
    else {
        insert(root, root, s);
    }
}

void Tree::insert(Node *curr, Node *prev, const string &s) {
    // Case 1: no children
    if (!curr->left && !curr->middle && !curr->right) {
        // Case 1a: 2 nodes
        if (curr->small != "" && curr->large != "") {
            split(curr, prev, 0, 0, s);
        }
        else if (s > curr->small) {
            curr->large = s;
        }
        else {
            curr->large = curr->small;
            curr->small = s;
        }
    }
    // Case 2: 1 child
    else if (curr->large == "") {
        if (s < curr->small) {
            insert(curr->left, curr, s);
        }
        else {
            insert(curr->middle, curr, s);
        }
    }
    // Case 3: 2 children
    else {
        if (s < curr->small) {
            insert(curr->left, curr, s);
        }
        else if (s <= curr->large) {
            insert(curr->middle, curr, s);
        }
        else {
            insert(curr->right, curr, s);
        }
    }
}


void Tree::split(Node* n, Node* parent, Node* lChild, Node* rChild, const string & s) {
    // S - Small
    // M - Middle
    // L - Large
    
    if (lChild && rChild) {
        // previous split is on middle child
        // rearrange chidren
        if (n->middle == lChild) { 
            Node* SLeft = n->left;
            Node* LRight = n->right;
            Node* large = new Node;
            
            string middle = "";
            
            set(n, large, middle, s);
            
            n->left = SLeft;
            n->right = 0;
            n->middle = lChild;
            
            large->parent = n->parent;
            large->left = rChild;
            large->middle = LRight;
            
            // node is root --> middle becomes new root
            if (n == root) { 
                root = new Node(middle);
                root->left = n;
                root->middle = large;
                
                n->parent = root;
                large->parent = root;
                return;
            }
            
            // middle value is pushed to make 2 node
            if (parent->large == "") { 
                if (middle < parent->small) {
                    parent->large = parent->small;
                    parent->small = middle;
                }
                else {
                    parent->large = middle;
                }
                parent->right = parent->middle;
                parent->middle = large;
            }
            // if parent is also a 2 node
            else {
                split(parent, parent->parent, n, large, middle);
            }
        }
        // split of left child
        else if (n->left == lChild) {
            Node* LLeft = n->middle;
            Node* LRight = n->right;
            Node* large = new Node;
            
            string middle = "";
            
            set(n, large, middle, s);
            
            n->left = lChild;
            n->middle = rChild;
            
            large->parent = n->parent;
            large->left = LLeft;
            large->middle = LRight;
            
            // same n = root, middle becomes new root
            if (n == root) {
                root = new Node(middle);
                root->left = n;
                root->middle = large;
                
                n->parent = root;
                large->parent = root;
                return;
            }
            
            // middle is pushed up into 1 node
            if (parent->large == "") {
                if (middle < parent->small) {
                    parent->large = parent->small;
                    parent->small = middle;
                }
                else {
                    parent->large = middle;
                }
                parent->left = large;
            }
            // middle is pushed up into 2 node
            else {
                split(parent, parent->parent, n, large, middle);
            }
        }
        // split on right child
        else { 
            Node* SLeft = n->left;
            Node* SRight = n->middle;
            Node* large = new Node;
            
            string middle = "";
            
            set(n, large, middle, s);
            
            n->left = SLeft;
            n->middle = SRight;
            n->right = 0;
            
            large->parent = n->parent;
            large->left = lChild;
            large->middle = rChild;
            
            // middle becomes new root
            if (n == root) {
                root = new Node(middle);
                root->left = n;
                root->middle = large;
                
                n->parent = root;
                large->parent = root;
                return;
            }
            
            // middle pushed to 1 node
            if (parent->large == "") {
                if (middle < parent->small) {
                    parent->large = parent->small;
                    parent->small = middle;
                }
                else {
                    parent->large = middle;
                }
                parent->right = large;
            }
            // middle pushed to 2 node
            else {
                split(parent, parent->parent, n, large, middle);
            }
        }
    }
    // split is not root
    else { 
        Node* largest = new Node;
        
        string midVal = "";
        
        set(n, largest, midVal, s);
        
        // middle becomes new root
        if (n == root) {
            root = new Node(midVal);
            root->left = n;
            root->middle = largest;
            root->right = 0;
            
            n->parent = root;
            largest->parent = root;
            return;
        }
        
        //middle pushed to 1 node
        if (parent->large == "") { 
            // children assigned to correct sides
            if (parent->left == n) { 
                if (parent->small < midVal) {
                    parent->large = midVal;
                }
                else {
                    parent->large = parent->small;
                    parent->small = midVal;
                }
                parent->right = parent->middle;
                parent->middle = largest;
                largest->parent = parent;
            }
            else {
                if (parent->small < midVal) {
                    parent->large = midVal;
                }
                else {
                    parent->large = parent->small;
                    parent->small = midVal;
                }
                parent->right = largest;
                largest->parent = parent;
            }

        }
        else { 
            // split performed again to top
            split(parent, parent->parent, n, largest, midVal);
        }
    }
}

void Tree::set(Node * n, Node * & large, string & middle, const string & s) { 
    // sets smallest / middle / largest 
    if (s < n->small) {
        middle = n->small;
        n->small = s;
        large->small = n->large;
        n->large = "";
    }
    else if (s <= n->large) {
        middle = s;
        large->small = n->large;
        n->large = "";
    }
    else {
        large->small = s;
        middle = n->large;
        n->large = "";
    }
}

// ========================================================================================================
// REMOVAL ----------------------------------------------------------------------------------------
// ========================================================================================================

void Tree::remove(const string &s) {
    if (!root || !(search(s))) {
        return;
    }
    
    remove(root, s);
}

void Tree::remove(Node* n, const string & s) { 
    if (n) {
        // found string 
        if (s == n->small || s == n->large) {
            // string is at root
            // no child 
            if (n == root && !n->left) {
                // 1 node
                if (n->large == s) {
                    n->large = "";
                    return;
                }
                // 2 node
                else if (n->small == s && n->large != "") {
                    n->small = n->large;
                    n->large = "";
                    return;
                }
                
                delete root;
                root = 0;
                return;
            }
            
            Node *succ = inorderSucc(n);
            
            // succ is value
            // large n exists in leaf
            if (succ == n) {
                if (n->large != "") {
                    n->large = n->small;
                    n->large = "";
                    return;
                }
            }
            
            // swap
            if (n->small == s) { 
                string temp = succ->small;
                succ->small = n->small;
                n->small = succ->small;
            }
            else if (n->large == s) {
                string temp = n->large;
                n->large = succ->small;
                succ->small = n->large;
            }
            
            if (succ->large != "") {
                succ->small = succ->large;
                succ->large = "";
            }
            else {
                succ->small = "";
                fix(succ, succ->parent);
            }
        }
        // find node that needs to be removed
        else if (s < n->small) { 
            remove(n->left, s);
        }
        else if (n->large == "" || s <= n->large) {
            remove(n->middle, s);
        }
        else {
            remove(n->right, s);
        }
    }
}

Node *Tree::inorderSucc(Node* n) {
    if (n->middle) {
        n = n->middle;
    }
    else {
        if (n->right) {
            n = n->right;
        }
    }
    
    while (n->left) {
        n = n->left;
    }
    
    return n;
}

void Tree::fix(Node* succ, Node* parent) {
    // succ is root, just delete it
    if (succ == root) {
        delete root;
        root = 0;
    }
    else {
        // children have some to spare
        if ((parent->left->large != "" && parent->left != succ) || 
            (parent->right->large != "" && parent->right != succ) || 
            (parent->middle->large != "" && parent->middle != succ)) {
            
            redistribute(succ, parent); 
        } 
        else {
            merge(succ, parent);
        }
        
        if (parent->small == "") {
            fix(parent,parent->parent);
        }
    }
}

void Tree::redistribute(Node* succ, Node* parent) {
    // right child empty
    if ((parent->left && parent->left->large != "") || 
        ((parent->middle && parent->middle->large != "") && 
        parent->right == succ)) { 
            
        if (parent->middle->large != "") {
            succ->small = parent->large;
            
            parent->large = parent->middle->large;
            parent->middle->large = "";
        }
        else {
            succ->small = parent->large;
            
            parent->large = parent->middle->small;
            parent->middle->small = parent->small;
            parent->small = parent->left->large;
            parent->left->large = "";
        }
    }
    // middle child empty
    else if ((parent->left && parent->left->large != "") || 
            ((parent->right && parent->right->large != "") && 
            parent->middle == succ)) {
        
        if (parent->large == "") {
            succ->small = parent->small;
            
            parent->small = parent->left->large;
            parent->left->large = "";
        }
        else if (parent->right->large != "") {
            succ->small = parent->large;
            
            parent->large = parent->right->small;
            parent->right->small = parent->right->large;
            parent->right->large = "";
        }
        else {
            succ->small = parent->small;
            
            parent->small = parent->left->large;
            parent->left->large = "";
        }
    }
    // left child empty
    else if ((parent->middle && parent->middle->large != "")  || 
            ((parent->right && parent->right->large != "") && 
            parent->left == succ)) { 
                
        if (parent->large == "") {
            succ->small = parent->small;
            
            parent->small = parent->middle->small;
            parent->middle->small = parent->middle->large;
            parent->middle->large = "";
        }
        else if (parent->middle->large != "") {
            succ->small = parent->small;
            
            parent->small = parent->middle->small;
            parent->middle->small = parent->middle->large;
            parent->middle->large = "";
        }else {
            succ->small = parent->small;
            
            parent->small = parent->middle->small;
            parent->middle->small = parent->large;
            parent->large = parent->right->small;
            parent->right->small = parent->right->large;
            parent->right->large = "";
        }
    }
} 

void Tree::merge(Node* n, Node* parent) {
    if (!n->left) {
        // middle merged together
        if (parent->middle == n) { 
            if (parent->large != "") {
                parent->left->large = parent->small;
                parent->small = parent->large;
                parent->large = "";
                
                n->small = parent->right->small;
                
                delete parent->right;
                parent->right = 0;
            }
        }
        // right merged
        else if (parent->right == n) { 
            if (parent->large != "") {
                parent->middle->large = parent->large;
                parent->large = "";
                
                delete parent->right;
                parent->right = 0;
            }
        }
        // left merged
        else {
            if (parent->large != "") { 
                parent->left->small = parent->small;
                parent->left->large = parent->middle->small;
                parent->middle->small = parent->right->small;
                parent->small = parent->large;
                parent->large = "";
                
                delete parent->right;
                parent->right = 0;
            }
        }
    }
}

// ========================================================================================================
// SEARCH ----------------------------------------------------------------------------------------
// ========================================================================================================

bool Tree::search(const string &s) const {
    string OMG = "";
    
    search(root, s, OMG);
    
    if (OMG == "OK") {
        return true;
    }
    
    return false;
}

void Tree::search(Node *n, const string &s, string &pass) const {
    if (n) {
        if (n->small == s || n->large == s) {
                pass = "OK";
        }
        else {
            if (s < n->small) {
                search(n->left, s, pass);
            } 
            else if (s <= n->large || n->large == "") {
                search(n->middle, s, pass);
            }
            else {
                search(n->right, s, pass);
            }
        }
    }
}
