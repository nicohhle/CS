#include <iostream>

using namespace std;

double mean(const double array[], int arraySize) {
    double sum = 0;
    
    for (int i = 0; i < arraySize; ++i) {
        sum = sum + array[i];
    }
    
    return sum / arraySize;
}

void remove(double array[], int &arraySize, int index) {
    for (int i = index; i < arraySize - 1; ++i) {
        array[i] = array[i + 1];
    }
    
    arraySize = arraySize - 1;
}

void display(const double array[], int arraySize) {
    for (int i = 0; i < arraySize - 1; ++i) {
        cout << array[i] << ", ";
    }
    
    cout << array[arraySize - 1];
    cout << endl;
}

int main() {
    
    int size = 10;
    double array[size];
    double meanVal = 0.0;
    int index;
    
    cout << "Enter 10 values:" << endl;
    
    for (int i = 0; i < size; ++i) {
        cin >> array[i];
    }
    
    cout << endl;
    
    meanVal = mean(array, size);
    cout << "Mean: " << meanVal << endl;
    cout << endl;
    
    cout << "Enter index of value to be removed: ";
    cin >> index;
    cout << endl;
    
    cout << "Before removing value: ";
    display(array, size);
    
    remove(array, size, index);
    
    cout << "After removing value: ";
    display(array, size);
    
    return 0;
}