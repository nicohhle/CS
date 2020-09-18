#include <iostream>
#include <string>

using namespace std;

class Rational {
   private:
      int numerator;
      int denominator; 
   public:
      Rational();
      explicit Rational(int); 
      Rational(int, int); 
      const Rational add(const Rational &) const; 
      const Rational subtract(const Rational &) const; 
      const Rational multiply(const Rational &) const; 
      const Rational divide(const Rational &) const;
      void simplify();
      void display() const;
   private:
      int gcd(int, int) const;
};

int Rational::gcd(int n, int d) const {
    int gcd;
    for (int i = 1; (i <= n && i <= d); ++i) {
        if (n % i == 0 && d % i == 0) {
            gcd = i;
        }
    }
    
    return gcd;
}

Rational::Rational() {
    numerator = 0;
    denominator = 1;
    return;
}

Rational::Rational(int numer) {
    numerator = numer;
    denominator = 1;
    return;
}

Rational::Rational(int numer, int denom) {
    numerator = numer;
    denominator = denom;
    return;
}

Rational const Rational::add(const Rational &item) const {
    Rational add;
    
    add.numerator = (numerator * item.denominator) + (denominator * item.numerator);
    add.denominator = (denominator * item.denominator);
    
    return add;
}

Rational const Rational::subtract(const Rational &item) const {
    Rational sub;
    
    sub.numerator = (numerator * item.denominator) - (denominator * item.numerator);
    sub.denominator = denominator * item.denominator;
    
    return sub;
}

Rational const Rational::multiply(const Rational &item) const {
    Rational mult;
    
    mult.numerator = numerator * item.numerator;
    mult.denominator = denominator * item.denominator;
    
    return mult;
} 

Rational const Rational::divide(const Rational &item) const {
    Rational divide;
    
    divide.numerator = (numerator * item.denominator);
    divide.denominator = (denominator * item.numerator);
    
    return divide;
}

void Rational::simplify() {
    int dividend = gcd(numerator, denominator);
    numerator = numerator / dividend;
    denominator = denominator / dividend;
}

void Rational::display() const {
    
    cout << numerator << " / " << denominator;
    
    return;
}

Rational getRational();
void displayResult(const string &, const Rational &, const Rational&, const Rational&);

int main() {
   Rational A, B, result;
   int choice;

   cout << "Enter Rational A:" << endl;
   A = getRational();
   cout << endl;

   cout << "Enter Rational B:" << endl;
   B = getRational();
   cout << endl;

   cout << "Enter Operation (1 - 4):" << endl
      << "1 - Addition (A + B)" << endl
      << "2 - Subtraction (A - B)" << endl
      << "3 - Multiplication (A * B)" << endl
      << "4 - Division (A / B)" << endl
      << "5 - Simplify A" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      result = A.add(B);
      displayResult("+", A, B, result);
   } else if (choice == 2) {
      result = A.subtract(B);
      displayResult("-", A, B, result);
   } else if (choice == 3) {
      result = A.multiply(B);
      displayResult("*", A, B, result);
   } else if (choice == 4) {
      result = A.divide(B);
      displayResult("/", A, B, result);
   } else if (choice == 5) {
      A.simplify();
      A.display();
   } else {
      cout << "Unknown Operation";
   }
   cout << endl;

   return 0;
}

Rational getRational() {
   int choice;
   int numer, denom;

   cout << "Which Rational constructor? (Enter 1, 2, or 3)" << endl
      << "1 - 2 parameters (numerator & denominator)" << endl
      << "2 - 1 parameter (numerator)" << endl
      << "3 - 0 parameters (default)" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      cout << "denominator? ";
      cin >> denom;
      cout << endl;
      return Rational(numer, denom);
   } else if (choice == 2) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      return Rational(numer);
   } else {
      return Rational();
   }
}

void displayResult(const string &op, const Rational &lhs, const Rational&rhs, const Rational &result) {
   cout << "(";
   lhs.display();
   cout << ") " << op << " (";
   rhs.display();
   cout << ") = (";
   result.display();
   cout << ")";
}