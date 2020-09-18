#include <iostream>

using namespace std;

int Gcd (int n1, int n2) {
    // return (n2 == 0) ? n1 : Gcd (n2, n1 % n2);
    
    int ok = n1 % n2;
    if (ok == 0) {
        return n2;
    }
    
    return Gcd(n2, ok);
}

/* Returns true if a solution was found and false if there is no solution.
   x and y will contain a solution if a solution was found. 
   This function will NOT output anything.
*/
bool diophantine(int a, int b, int c, int &x, int &y) {
    int gcd = Gcd(a, b);
    
    if (c % gcd != 0) {
        return false;
    }
    if (a % b == 0) {
        x = 0;
        y = c / b;
        return true;
    } else {
        int r = a % b;
        int v = x;
        int u;
        
        // like GCD, change a and b into b and remainder
        // check if get solution u, v
        // use equations from assignment 
        if (diophantine(b, r, c, u, v)) {
            int q = a / b;
            x = v;
            y = u - (q * x);
            return true;
        }
        
        // check if solution is right (== c)
        if ((a * x) + (b * y) == c) {
            return true;
        }
        
        return false;
    }
    
    return false;
}

int main() {
    int a, b, c, x, y;

    cout << "Enter a b c" << endl;
    cin >> a >> b >> c;
    cout << endl;
    
    cout << "Result: ";
    if (diophantine(a, b, c, x, y)) {
        cout << x << " " << y << endl;
    } else {
        cout << "No solution!" << endl;
    }

    return 0;
}

// int main() {
//     int a, b, c, x, y;
    
//     a = 28;
//     b = 7;
//     c = 490;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "0 70 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 11;
//     b = 11;
//     c = 2010;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "No solution! = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 1984;
//     b = 3070;
//     c = 1;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "No solution! = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 200;
//     b = -2;
//     c = 4;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "0 -2 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 25;
//     b = 75;
//     c = 100;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "4 0 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 25;
//     b = 75;
//     c = 1000;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "40 0 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 25;
//     b = 75;
//     c = 1;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "No solution! = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 12;
//     b = 24;
//     c = 48;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "4 0 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 1024;
//     b = 96;
//     c = 2048;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "-64 704 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 5;
//     b = -29;
//     c = 6;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "36 6 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 395;
//     b = 252;
//     c = 1;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "-37 58 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = 25;
//     b = 38;
//     c = 2;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "-6 4 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }
    
//     cout << endl;
    
//     a = -10;
//     b = -10;
//     c = 100;
    
//     cout << a << " " << b << " " << c << endl;
//     cout << "Gcd: " << Gcd(a, b) << endl;
//     cout << "0 -10 = ";
//     if (diophantine(a, b, c, x, y)) {
//         cout << x << " " << y << endl;
//     } else {
//         cout << "No solution!" << endl;
//     }

//     return 0;
// }