#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>


using namespace std;

#include "WordLadder.h"
 
    /* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file. 
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
    */

WordLadder::WordLadder(const string &filename) {
    ifstream file;
    string word;
    
    file.open(filename.c_str());
    
    if (!file.is_open()) {
        cout << "File could not be opened" << endl;
    }
    
    while (file >> word) {
        if (word.size() == 5) {
            dict.push_back(word);
        } else {
            cout << "Error" << endl;
        }
    }
    
    
    file.close();
}

    /* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    ofstream file;
    
    file.open(outputFile.c_str());
    
    if (!file.is_open()) {
        cout << "File could not be opened" << endl;
    }
    
    if (start == end) {
        file << start;
        file.close();
        return;
    }
    
    stack <string> stk;
    stk.push(start);
   
    queue < stack<string> > que;
    que.push(stk);
   
    string curr = que.front().top();
        
    while (!que.empty()) {
        for (list<string> :: iterator it = dict.begin(); it != dict.end(); it++) {
            string nextword = *it;
            if (LetterOff(curr, nextword)) {
                stack <string> newStk(que.front());
                
                newStk.push(nextword);
                
                if (*it == end) {
                    Print(newStk, file);
                    return;
                } else {
                    que.push(newStk);
                    it = dict.erase(it);
                    it--;
                }
            }
            
            curr = que.front().top();
        }
        
        que.pop();
    }
   
    file << "No Word Ladder Found.";
    file.close();
}

bool WordLadder::LetterOff(const string &og, const string &check) {
    int count = 0;
    
    if (og.size() != 5 || check.size() != 5) {
        return false;
    }
    
    for (int i = 0; i < 5; ++i) {
        if (check.at(i) != og.at(i)) {
            ++count;
        } else {
            count = count;
        }
    }
    
    if (count == 1) {
        return true;
    } else {
        return false;
    }
}

void WordLadder::Print(stack <string> &s, ofstream &out) {
    if (s.empty()) {
        return;
    } else {
        string front = s.top();
        
        // out << front << " ";
        // s.pop();
        // Print(s, out);
        
        s.pop();
        Print(s, out);
        out << front << " ";
    }
}
