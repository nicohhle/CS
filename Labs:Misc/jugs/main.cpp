#include <iostream>
#include <string>

#include "Jug.h"

using namespace std;

int main() {
    
   string solution;
   Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
   Jug head2( 3, 5, 4, 1, 1, 1, 1, 1, 2);         
   
   if (head.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   
   if(head2.solve(solution) != 1) {
      cout << "Error 3" << endl;
   }
   cout << solution << endl;
    
    return 0;
}

//when running code add -std=c++11 to the end of command