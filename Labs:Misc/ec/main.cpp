#include <iostream>

using namespace std;

//counter to keep track of how many times to print
//acts like loop without actually using for/while ...
int count = 1;

class Print
{
  public:
    Print();
    ~Print();
};

Print::Print()
{
    cout << count << " ";
    // cout << " " << count;
    count++;
}

Print::~Print()
{
    //nothing to delete
}

int main() 
{
    int num;
    
    // cout << "Enter a number to print out all the previous:\n";
    
    cin >> num;
    
    // cout << count++;
    
    Print temp[num - 1];
    cout << count;
    
    cout << endl;
    
    return 0;
}