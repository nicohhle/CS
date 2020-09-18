#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

#include "arithmeticExpression.h"

    /* Initializes an empty tree and sets the infixExpression
    to the value of parameter passed in. */

arithmeticExpression::arithmeticExpression(const string &infixEx) {
    root = 0;
    infixExpression = infixEx;
}

    /* Implementation of destrucor is optional.
       The destructor should deallocate all the nodes in the tree. */
    //~arithmeticExpression();

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree() {
    string postfix = infix_to_postfix();
    stack<TreeNode *> nodes;
    /*
    
    for (unsigned i = 0; i < postfix.size(); ++i) {
        nodes.push(postfix.at(i));
    }
    
    root = nodes.top();
    nodes.pop();
    
    int rootPriority = priority(nodes.top());
    if (priority(s.top())) {
        
    }
    */
    /*
    char key = 'a';
    for (unsigned i = 0; i < postfix.size(); i++) {
        char c = postfix.at(i);
        //priority means we have an operator, so we take the previous two nodes in the stack and combine them with this operator
        if(priority(c)) {
            TreeNode *n = new TreeNode(c, key);
            
            n->right = nodes.top();
            nodes.pop();
            n->left = nodes.top();
            nodes.pop();
            key++;
        } else {
            //Otherwise we turn this into a node
            nodes.push(new TreeNode(c, key));
            key++;
        }
    }
    */
    char k = 'a';
    for (unsigned i = 0; i < postfix.size(); ++i) {
        TreeNode *tree = new TreeNode(postfix.at(i), k++);
        
        if (postfix.at(i) == '+' || postfix.at(i) == '-' || postfix.at(i) == '*' || postfix.at(i) == '/') {
            tree->right = nodes.top();
            nodes.pop();
            tree->left = nodes.top();
            nodes.pop();
            nodes.push(tree);
        } else {
            nodes.push(tree);
        }
    }
    
    root = nodes.top();
}

    /* Calls the recursive infix function. */
void arithmeticExpression::infix() { 
    infix(root); 
}

    /* Calls the recursive prefix function. */
void arithmeticExpression::prefix() { 
    prefix(root); 
}

    /* Calls the recursive postfix function. */
void arithmeticExpression::postfix() {
    postfix(root);
}

    /* Calls the recursive visualizeTree function and generates the .png file using system call. */
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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
    
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

       /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the 
       beginning and ending of each expression. */
void arithmeticExpression::infix(TreeNode *n) {
    if(!n) {
        return;
    } // else if (n->left || n->right) {
        if (n->left) {
            cout << "(";
        }
        infix(n->left);
        cout << n->data;
        infix(n->right);
        if (n->right) {
            cout << ")";
        }
    // } else {
    //     cout << n->data;
    // }
}

    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
void arithmeticExpression::prefix(TreeNode *n) {
    if(!n) {
        return;
    } else {
        cout << n->data;
        prefix(n->left);
        prefix(n->right);
    }
}
    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
void arithmeticExpression::postfix(TreeNode *n) {
    if (n) {
        postfix(n->left);
        postfix(n->right);
        cout << n->data;
    }
}

    /* Helper function for generating the dotty file. This is a recursive function. */
void arithmeticExpression::visualizeTree(ofstream &out, TreeNode *n) {
    out << n->key << "[label=\"" << n->data << "\"];";
    
    if (!n) {
        return;
    }
    
    if (n->left) {
        out << n->key << "->" << n->left->key << ";";
        visualizeTree(out, n->left);
    }
    
    if (n->right) {
        out << n->key << "->" << n->right->key << ";";
        visualizeTree(out, n->right);
    }
}