#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>

using namespace std;

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    T min = vals.at(index);
    unsigned value = index;
    
    for (unsigned i = index; i < vals.size(); ++i) {
        if (vals.at(i) < min) {
            min = vals.at(i);
            value = i;
        }
    }
    
    return value;
}

template <typename T>
void selection_sort(vector<T> &vals) {
    for (unsigned i = 0; i < vals.size(); ++i) {
        unsigned min = min_index(vals, i);
        
        T temp = vals.at(i);
        vals.at(i) = vals.at(min);
        vals.at(min) = temp;
    }
}

vector<char> createVector() {
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
 
    return vals;
}

template <typename T>
T getElement(vector<T> vals, int index) {
    return vals.at(index);
}

int main(){

    //Part B
    try {
        srand(time(0));
        vector<char> vals = createVector();
        char curChar;
        int index;
        int numOfRuns = 10;
        while(--numOfRuns >= 0){
            cout << "Enter a number: " << endl;
            cin >> index;
            
            if (index >= static_cast<int>(vals.size()) || index < 0) {
                throw std::out_of_range("out of range");
            }
             
                curChar = getElement(vals,index);
                cout << "Element located at " << index << ": is " << curChar << endl;
        } 
    } catch (const std::out_of_range &excpt) {
            cout << excpt.what() << endl;
        }

    return 0;
}