#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "AVLTree.h"
#include "Node.h"

AVLTree::AVLTree() {
    root = 0;
}
// ========================================================================================================
// HEIGHT FUNCTION ----------------------------------------------------------------------------------------
// ========================================================================================================

int AVLTree::getHeight(Node *n) {
    if (n) {
        if (!n->hasChild()) {
            return 0;
        }
        
        int left = getHeight(n->left) + 1;
        int right = getHeight(n->right) + 1;
        
        if (left < right) {
            return right;
        } else {
            return left;
        }
    }
    
    return -1;
}

// ========================================================================================================
// INSERT FUNCTIONS ----------------------------------------------------------------------------------------
// ========================================================================================================

void AVLTree::insert(const string &s) {
    if (!root) {
        cout << "root " << s << endl;
        root = new Node(s);
        return;
    } 
    
    Node *n = root;
    insert(n, s);
}

void AVLTree::insert(Node *n, const string &s) {
    if (s < n->str) {
        if (n->left == 0) {
            n->left = new Node(s);
            
            Node *balanceL = findUnbalancedNode(n->left);
            
            if (balanceL) {
                rotate(balanceL);
            }
            
            return;
        }
        else {
            insert(n->left, s);
        }
    } 
    else if (s > n->str) {
        if (n->right == 0) {
            n->right = new Node(s);
            
            Node *balanceR = findUnbalancedNode(n->right);
            
            if (balanceR) {
                rotate(balanceR);
            }
            
            return;
        }
        else {
            insert(n->right, s);
        }
    }
}

// ========================================================================================================
// ROTATION ----------------------------------------------------------------------------------------
// ========================================================================================================

// Helper site on rotation:
// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

void AVLTree::rotate(Node *n) {
    // LL and LR Case
    if (balanceFactor(n) > 1) {
        if (balanceFactor(n->left) > 0) {
            rotateRight(n);
        } 
        else if (balanceFactor(n->left) < 0) {
            rotateLeft(n->left);
            rotateRight(n);
        }
    }
    
    // RR and RL Case
    else if (balanceFactor(n) < -1) {
        if (balanceFactor(n->right) < 0) {
            rotateLeft(n);
        }
        else if (balanceFactor(n->right) > 0) {
            rotateRight(n->right);
            rotateLeft(n);
        }
    }
}

Node * AVLTree::rotateLeft(Node *n) {
    // // if (n->right) {
    //     Node *newroot = n->right;
    
    //     // if (newroot->left) {
    //         Node *l = newroot->right;
        
    //         if (n == root) {
    //             root = newroot;
    //         }
            
    //         n->right = newroot->left;
    //         newroot->left = n;
            
    //         // if (newroot->right == 0) {
    //         //     newroot->right = l;
    //         // }
    //         // else {
    //             // n->right = l;
    //         // }
    //     // }
        
    //     return newroot;
    // // }
    
    Node *newroot = n->right;
    Node *l = newroot->left;
    
    newroot->left = n;
    n->right = l;
    
    return newroot;
}

Node * AVLTree::rotateRight(Node *n) {
    // // if (n->left) {
    //     Node *newroot = n->left;
    
    //     // if (newroot->right) {
    //         Node *r = newroot->left;
        
    //         if (n == root) {
    //             root = newroot;
    //         }
            
    //         n->left = newroot->right;
    //         newroot->right = n;
            
    //         // if (newroot->left == 0) {
    //         //     newroot->left = r;
    //         // }
    //         // else {
    //             n->left = r;
    //         // }
    //     // }
        
    //     return newroot;
    // // }
    
    Node *newroot = n->left;
    Node *r = newroot->right;
    
    newroot->right = n;
    n->left = r;
    
    return newroot;
}

// ========================================================================================================
// BALANCE FACTORS ----------------------------------------------------------------------------------------
// ========================================================================================================

int AVLTree::balanceFactor(Node *n) {
    if (!n) {
        return -1;
    } 
    else if (!(n->hasChild())) {
        return 0;
    }
    else {
        return getHeight(n->left) - getHeight(n->right);
    }
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
}

void AVLTree::printBalanceFactors(Node *n) {
    if (n) {
        printBalanceFactors(n->left);
        cout << n->str << "(" << balanceFactor(n) << "), ";
        printBalanceFactors(n->right);
    }
}

Node * AVLTree::findUnbalancedNode(Node *n) {
    if (n) {
        if (balanceFactor(n) < -1 || balanceFactor(n) > 1) {
            return n;
        }
        
        // must go up tree when finding balance
        if (n != root) {
            return findUnbalancedNode(findParent(n, root));
        }
    }
    
    return 0;
}

// ========================================================================================================
// FIND PARENT ----------------------------------------------------------------------------------------
// ========================================================================================================

Node * AVLTree::findParent(Node *n, Node *start) const {
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
    
    return 0;
}

// ========================================================================================================
// VISUALIZE TREE ----------------------------------------------------------------------------------------
// ========================================================================================================

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->str <<" -> " <<n->left->str<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->str <<" -> " <<n->right->str<<";"<<endl;    
        }
    }
}