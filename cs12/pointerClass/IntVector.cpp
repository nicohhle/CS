#include <iostream>
#include <stdexcept>

using namespace std;

#include "IntVector.h"

IntVector::IntVector() {
    sz = 0;
    cap = 0;
    data = 0;
}

IntVector::IntVector(unsigned size, int value) {
    sz = size;
    cap = size;
    
    data = new int[size];
    
    for (unsigned int i = 0; i < sz; ++i) {
        data[i] = value;
    }
}

IntVector::~IntVector() {
    delete []data;          // []data is later, can just do delete data now
}

unsigned IntVector::size() const {
    return sz;
}

unsigned IntVector::capacity() const {
    return cap;
}

bool IntVector::empty() const {
    if (sz == 0) {
        return true;
    }
    
    return false;
}

const int& IntVector::at(unsigned index) const {
    if (index >= sz) {
        throw out_of_range("IntVector::at_range_check");
    }
    
    return data[index];
}

int& IntVector::at(unsigned index) {
    if (index >= sz) {
        throw out_of_range("IntVector::at_range_check");
    }
    
    return data[index];
}

void IntVector::insert(unsigned index, int value) {
    if (index > sz) {
        throw out_of_range("IntVector::insert_range_check");
    }
    
    if (sz >= cap) {
        expand();
    }
    
    sz = sz + 1;
    
    for (unsigned int i = sz - 1; i > index; --i) {
        data[i] = data[i - 1];
    }
    
    data[index] = value;
}

void IntVector::erase(unsigned index) {
    if (index >= sz) {
        throw out_of_range("IntVector::erase_range_check");
    }
    
    for (unsigned int i = index; i < sz - 1; ++i) {
        data[i] = data[i + 1];
    }
    
    sz = sz - 1;
}

const int& IntVector::front() const {
    return data[0];
}

int& IntVector::front() {
    return data[0];
}

const int& IntVector::back() const {
    return data[sz - 1];
}

int& IntVector::back() {
    return data[sz - 1];
}

void IntVector::assign(unsigned n, int value) {
    // resize(n, value);
        
    if (n >= cap * 2) {
        expand(n - cap);
        
        if (cap == 1) {
            expand(n - cap);
        }
    } else if (n >= cap) {
        expand();
        
        if (cap == 1) {
            expand(n - cap);
        }
    }
    
    sz = n;
    
    for (unsigned int i = 0; i < sz; ++i) {
        data[i] = value;
    }
}

void IntVector::push_back(int value) {
    if (sz + 1 > cap) {
        expand();
    }
    
    sz = sz + 1;
    data[sz - 1] = value;
}

void IntVector::pop_back() {
    if (sz == 0) {
        return;
    }
    
    sz = sz - 1;
}

void IntVector::clear() {
    sz = 0;
}

void IntVector::resize(unsigned size, int value) {
    int oldSz;
    
    if (size > cap * 2) {
        expand(size - cap);
        
        if (cap == 1) {
            expand(size-cap);
        }
    } else if (size >= cap) {
        expand();
        
        if (cap == 1) {
            expand(size - cap);
        }
    }
        
    if (size < sz) {
        sz = size;
    } else if (size > sz) {
        oldSz = sz;
        sz = size;
        
        for (unsigned int i = oldSz; i < sz; ++i) {
            data[i] = value;
        }
    }
}

void IntVector::reserve(unsigned n) {
    if (n > cap) {
        cap = n;
    }
}

void IntVector::expand() {
    if (cap != 0) {
        cap = cap * 2;
    
        int *temp = data;
        data = new int[cap];
        
        for (unsigned int i = 0; i < sz; ++i) {
            data[i] = temp[i];
        }
        
        // delete temp;
    } else if (cap == 0) {
        cap = 1; 
        data = new int[cap];
    }
}

void IntVector::expand(unsigned amount) {
    if (cap != 0) {
        cap = cap  + amount;
        int *temp = data;
        data = new int[cap];
        
        for (unsigned int i = 0; i < sz; ++i) {
            data[i] = temp[i];
        }
        
        // delete temp;
    } else if (cap == 0) {
        cap = 1; 
        data = new int[cap];
    }
}