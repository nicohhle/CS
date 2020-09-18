#include <iostream>

using namespace std;

#include "Distance.h"

Distance::Distance() {
    feet = 0;
    inches = 0.0;
    
    return;
}

Distance::Distance(unsigned ft, double in) {
    feet = ft;
    inches = in;
    
    if (feet < 0) {
        feet = feet * -1;
    }
    
    if (inches < 0) {
        inches = inches * -1;
    }
    
    while (inches >= 12) {
        feet = feet + 1;
        inches = inches - 12;
    }
    
    return;
}

Distance::Distance(double in) {
    feet = 0;
    inches = in;
    
    if (inches < 0) {
        inches = inches * -1;
    }
    
    while (inches >= 12) {
        feet = feet + 1;
        inches = inches - 12;
    }
}

/* ALTERNATE SOLN
Distance::Distanec(double in) {
    feet = 0;
    inches = in;
    
    int carrier = 0;
    
    if (inches >= 12) {
        carrier = static_cast<int>(in) / 12;
        feet = feet + carrier;
        inches = inches - (12 * carrier);
    }
}
*/

unsigned Distance::getFeet() const {
    return feet;
}

double Distance::getInches() const {
    return inches;
}

double Distance::distanceInInches() const {
    return (feet * 12) + inches;
}

double Distance::distanceInFeet() const {
    return (inches / 12) + feet;
}

double Distance::distanceInMeters() const {
    return distanceInInches() * 0.0254;
}

const Distance Distance::operator+(const Distance &rhs) const {
    Distance added;
    
    added.feet = feet + rhs.feet;
    added.inches = inches + rhs.inches;
    
    if (added.inches >= 12) {
        added.init();
    }
    
    return added;
}

const Distance Distance::operator-(const Distance &rhs) const {
    Distance subt;
    
    // if (rhs.feet > feet) {
    //     subt.feet = rhs.feet - feet;
    // } else if (rhs.inches > inches) {
    //     subt.inches = rhs.inches - inches;
    // }
    
    
    double temp = distanceInInches();
    double rhstemp = rhs.distanceInInches();
    double subtemp = temp - rhstemp;
    
    if (subtemp < 0) {
        subtemp = subtemp * -1;
    }
    
    subt.feet = static_cast<int>(subtemp) / 12;
    subt.inches = subtemp - (subt.feet * 12);
    
    return subt;
}

ostream & operator<<(ostream &out, const Distance &rhs) {
    out << rhs.feet << "' " << rhs.inches << "\"";
    
    return out;
}

void Distance::init() {
    if (feet < 0) {
        feet = feet * -1;
    }
    
    if (inches < 0) {
        inches = inches * -1;
    }
    
    while (inches >= 12) {
        feet = feet + 1;
        inches = inches - 12;
    }
    
    return;
}