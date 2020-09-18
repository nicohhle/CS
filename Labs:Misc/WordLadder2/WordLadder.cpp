#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>
#include <list>
#include <vector>
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
    ifstream ifile;
    string word;
    
    ifile.open(filename.c_str());
    
    if (!ifile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    while (ifile >> word) {
        if (word.size() == 5) {
            dict.push_back(word);
        } else {
            cout << "Error - word must be 5 letters" << endl;
            break;
        }
    }
    
    ifile.close();
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
    ofstream ofile;
    
    ofile.open(outputFile.c_str());
    
    if (!ofile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    // if there is only one entry, write that entry to output file and return
    if (start == end) {
        ofile << start;
        ofile.close();
        return;
    }
    
    // create a stack containing just the first word in the ladder
    stack<string> s;
    s.push(start);
    
    // enqueue this stack onto a queue of stacks
    queue< stack<string> > q;
    q.push(s);
    
    string top = q.front().top();
    
    // while the queue of stacks is not empty
    while (!q.empty()) {
        // get the word on top of the front stack of this queue
        // string top = q.front().top();
        
        // for each word in the dict
        // iteration for list : http://www.cplusplus.com/forum/general/22957/
        for (list<string> :: iterator it = dict.begin(); it != dict.end(); ++it) {
            
            // if the word is off by just one letter from the top word
            string next = *it;
            
            if (letterOff(top, next)) {
                
                // create a new stack that is a copy of the front stack + push on word
                stack<string> snew(q.front());
                snew.push(next);
                
                // if this word is the end word of ladder, this new stack is entire ladder -- PRINT
                if (*it == end) {
                    print(snew, ofile);
                    return;
                    
                } else {
                    
                    // enqueue new stack and remove this word from the dict
                    q.push(snew);
                    it = dict.erase(it);
                    it--;
                }
            }
            
            top = q.front().top();
        }
        
        // if not found, pop until empty
        q.pop();
    }
    
    // if queue is empty and you didn't find the word ladder, a word ladder does not exist
    ofile << "No Word Ladder Found." << endl;
    ofile.close();
}

bool WordLadder::letterOff(const string &old, const string &compare) {
    int count = 0;
    
    // check to see if they match and are 5 letters
    if (old.size() != 5 || compare.size() != 5) {
        return false;
    }
    
    // loop to compare the strings
    // if it's a letter off count will increment
    for (int i = 0; i < 5; ++i) {
        if (old.at(i) != compare.at(i)) {
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

void WordLadder::print(stack<string> &s, ofstream &out) {
    // check if empty, otherwise print
    if (s.empty()) {
        return;
    } else {
        string top = s.top();
        
        s.pop();
        // will return everytime after popping all elements 
        // pops from the top -- prints backwards
        print(s, out);
        out << top << " ";
    }
}