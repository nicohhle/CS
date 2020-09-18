#include <iostream>
using namespace std;

int main ( ) {
    
    int trunkHeight;
    int trunkWidth;
    int leavesWidth;
    
    cout << "Enter trunk height: ";
    cin >> trunkHeight;
    
    cout << "Enter trunk width: ";
    cin >> trunkWidth;
    
    while ((trunkWidth % 2) == 0) {
        cout << "Please enter an odd number for the width: ";
        cin >> trunkWidth;
    }
    
    cout << "Enter leaves width: ";
    cin >> leavesWidth;
    
    while ((leavesWidth % 2) == 0) {
        cout << "Please enter an odd number for the width: ";
        cin >> leavesWidth;
    }
    
    cout << endl;
    
    int halfLeaves;
    halfLeaves = leavesWidth / 2 + 1;
    
    for (int a = 0; a < ((leavesWidth / 2) + 1); ++a) {
        for (int b = halfLeaves - 1; b > 0; --b) {
            cout << " ";
        } 
        halfLeaves = halfLeaves - 1;
        
        for (int c = 1; c < ((a + 1) * 2); ++c) {
            cout << "*";
        }
       cout << endl;
    }
    
    for (int i = 0; i < trunkHeight; ++i) {
        for (int j = 0; j < ((leavesWidth - trunkWidth) / 2); ++j) {
            cout << " ";
        } for (int k = 0; k < trunkWidth; ++k) {
            cout << "*";
        }
        cout << endl;
    }
    
    return 0;
}