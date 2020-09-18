#include <iostream>
#include <string>

using namespace std;

//helper on ROT13 cipher concept
//https://en.wikipedia.org/wiki/ROT13

void cipher(string &s) {
    for (unsigned i = 0; i < s.size(); ++i) {
        if ((s[i] >= 'A') && (s[i] <= 'Z')) {
            s[i] = s[i] - 13;
            
            if (s[i] < 'A') {
                s[i] = s[i] + 26;
            }
            
        } 
        else if ((s[i] >= 'a') && (s[i] <= 'z')) {
            s[i] = s[i] - 13;
            
            if (s[i] < 'a') {
                s[i] = s[i] + 26;
            }
        }
    }
}

// int main() {
    
//     string secret;
//     cout << "Enter text\n";
//     getline(cin, secret);
    
//     cipher(secret);
//     cout << endl;
//     cout << secret;
    
//     return 0;
// }