#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "WordLadder.h"

int main() {
    
    string ifile, ofile, begin, end;
    
    cout << "Hey there!" << endl;
    
    cout << "Enter the name of the dictionary: ";
    cin >> ifile;
    cout << endl;
    
    cout << "Enter the name of the output file: ";
    cin >> ofile;
    cout << endl;
    
    cout << "Enter the first word: ";
    cin >> begin;
    cout << endl;
    
    while (begin.size() != 5) {
        cout << "Word must be 5 letters" << endl;
        cout << "Please choose another word: ";
        cin >> begin;
        cout << endl;
    }
    
    cout << "Enter the last word: ";
    cin >> end;
    cout << endl;
    
    while (end.size() != 5) {
        cout << "Word must be 5 letters" << endl;
        cout << "Please choose another word: ";
        cin >> end;
        cout << endl;
    }
    
    WordLadder w(ifile);
    w.outputLadder(begin, end, ofile);
    
    return 0;
}