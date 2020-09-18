#include <iostream>
#include <cstdlib>

using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    // pick middle value as pivot
    int mid = i + (k - i) / 2;
    int pivot = numbers[mid];
    bool done;
    
    int l = i;
    int h = k;
    
    while (!done) {
        // increment i while numbers[l] < pivot
        while (numbers[l] < pivot) {
            ++l;
        }
        
        // decrement h while pivot < numbers[h]
        while (pivot < numbers[h]) {
            --h;
        }
        
        // if there are 0 or 1 item remain, all numbers are partitioned -- return h
        if (l >= h) {
            done = true;
        }
        else {
            // swap numbers[l] and numbers[h]
            // update l and h
            int temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    int j = 0;
    
    // base case: 0 or 1 elements to sort --> already sorted
    if (i >= k) {
        return;
    }
    
    // partition data in array
    // j returned if location of last element in low partition
    j = h;
    
    // recursively sort low partition (i to j)
    //                  high partition (j+1 to k)
    Quicksort_midpoint(numbers, i, j);
    Quicksort_midpoint(numbers, j + 1, k);
}
/*: this function sorts the given array in the range from i to k using quicksort method. 
In this function, pivot is the midpoint element (numbers[(i+k)/2]). 
(implementation of this function is given in section 22.5)*/

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i >= k) {
        return;
    }
    int mid = i + (k - i) / 2;
    int pivot = 0;
    bool done;
    

    if ((numbers[i] <= numbers[mid] && numbers[i] >= numbers[k]) ||
        (numbers[i] >= numbers[mid] && numbers[i] <= numbers[k])) {
            pivot = numbers[i];
    }
    else if ((numbers[mid] <= numbers[i] && numbers[mid] >= numbers[k]) ||
             (numbers[mid] >= numbers[i] && numbers[mid] <= numbers[k])) {
                 pivot = numbers[mid];
    }
    else {
        pivot = numbers[k];
    }
    
    
    int l = i;
    int h = k;
    
    while (!done) {
        // increment i while numbers[l] < pivot
        while (numbers[l] < pivot) {
            ++l;
        }
        
        // decrement h while pivot < numbers[h]
        while (pivot < numbers[h]) {
            --h;
        }
        
        // if there are 0 or 1 item remain, all numbers are partitioned -- return h
        if (l >= h) {
            done = true;
        }
        else {
            // swap numbers[l] and numbers[h]
            // update l and h
            int temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
        }
    }
    
    int j = 0;
    
    // base case: 0 or 1 elements to sort --> already sorted
    
    
    // partition data in array
    // j returned if location of last element in low partition
    j = h;
    
    // recursively sort low partition (i to j)
    //                  high partition (j+1 to k)
    Quicksort_medianOfThree(numbers, i, j);
    Quicksort_medianOfThree(numbers, j + 1, k);
}
/*: this function utilizes different pivot selection technique in quicksort algorithm. 
The pivot is the median of the following three values: leftmost (numbers[i]), midpoint 
(numbers[(i+k)/2]) and rightmost (numbers[k]). You should modify the partition function 
given in section 22.5 to select the pivot using median-of-three technique.*/

void InsertionSort(int numbers[], int numbersSize) {
    for (int i = 1; i < numbersSize; ++i) {
        int j = i;

        // insert numbers[i] into sorted part
        // stop once numbers[i] in correct position
        while (j > 0 && numbers[j] < numbers[j - 1]) {
            // swap
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            
            --j;
        }
    }
}
/*: this function sorts the given array using InsertionSort method. 
(implementation of this method is provided in section 22.3).*/

int main() {
    
    clock_t Start1 = clock();
    //call sort function here
    int arr1[NUMBERS_SIZE], arr2[NUMBERS_SIZE], arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);
    
    Quicksort_midpoint(arr1, 0, 10);
    
    for (int i = 0; i < 10; ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    clock_t End1 = clock();
    int elapsedTime1 = (End1 - Start1)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime1 << endl;
    
// ------------------------------------------------------------------------------------------------------------------------------------------------------
    
    clock_t Start2 = clock();
    
    InsertionSort(arr1, NUMBERS_SIZE);
    
    for (int i = 0; i < rand() % 51 + 25; ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    clock_t End2 = clock();
    int elapsedTime2 = (End2 - Start2)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime2 << endl;
    
// ------------------------------------------------------------------------------------------------------------------------------------------------------

    clock_t Start3 = clock();
    
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    
    for (int i = 0; i < rand() % 41 + 20; ++i) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    clock_t End3 = clock();
    int elapsedTime3 = (End3 - Start3)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime3 << endl;

// ------------------------------------------------------------------------------------------------------------------------------------------------------
    
    clock_t Start4 = clock();
    
    InsertionSort(arr3, NUMBERS_SIZE);
    
    for (int i = 0; i < rand() % 26 + 10; ++i) {
        cout << arr3[i] << " ";
    }
    cout << endl;
    
    clock_t End4 = clock();
    int elapsedTime4 = (End4 - Start4)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << elapsedTime4 << endl;
    
    return 0;
}