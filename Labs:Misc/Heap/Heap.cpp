#include <iostream>

using namespace std;

#include "Heap.h"
#include "PrintJob.h"

Heap::Heap() {
    numItems = 0;
}

/*Inserts a PrintJob to the heap without
violating max-heap properties.*/
void Heap::enqueue (PrintJob *p) {
    if (numItems != MAX_HEAP_SIZE) {
        if (numItems == 0) {
            arr[numItems] = p;
            ++numItems;
        }
        else {
            int x = numItems;
            
            while (x > 0 && arr[(x - 1) / 2]->getPriority() < p->getPriority()) {
                arr[x] = arr[(x - 1) / 2];
                x = (x - 1) / 2;
            }
            
            arr[x] = p;
            ++numItems;
        }
    }
}

/*Removes the node with highest priority from the heap. 
Follow the algorithm on priority-queue slides. */
void Heap::dequeue() {
    if (numItems == 0) {
        cout << "Error: called dequeue on empty heap" << endl;
        return;
    }
    
    if (numItems == 1) {
        numItems--;
        return;
    } 
    else if (numItems == 2) {
        arr[0] = arr[1];
        numItems--;
        return;
    }
    
    // set last element as first ("swap")
    arr[0] = arr[numItems - 1];
    //decrement
    numItems--;
    trickleDown(0);
}

/*Returns the node with highest priority.*/
PrintJob* Heap::highest() {
    if (numItems == 0) {
        return 0;
    }
    
    return arr[0];
}

/*Prints the PrintJob with highest priority in the following format:
Priority: priority, Job Number: jobNum, Number of Pages: numPages
(Add a new line at the end.)*/
void Heap::print() {
    if (numItems > 0) {
        cout << "Priority: " << arr[0]->getPriority() << 
                ", Job Number: " << arr[0]->getJobNumber() << 
                ", Number of Pages: " << arr[0]->getPages() << endl;
    }
}

/*This function is called by dequeue function
to move the new root down the heap to the 
appropriate location.*/
void Heap::trickleDown(int n) {
    int left = (2 * n) + 1;
    int right = (2 * n) + 2;
    
    int max = n;
    
    //check if there are left and right children
    //if they exist, their indexes are less than numItems
    // set to max if greater than, then compare the new max
    if (left < numItems && arr[left]->getPriority() > arr[max]->getPriority()) {
        max = left;    
    }
    if (right < numItems && arr[right]->getPriority() > arr[max]->getPriority()) {
        max = right;
    }
    
    //if the new largest is not the same as the original
    // swap largest with the end
    if (max != n) {
        PrintJob *temp = arr[n];
        arr[n] = arr[max];
        arr[max] = temp;
        trickleDown(max);
    }
}