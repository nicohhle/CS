#include <iostream>
#include <string>

using namespace std;

#include "Character.h"

Character::Character(HeroType type, const string &name, double health, double attackStrength) {
    this->type = type;
    this->name = name;
    this->health = health;
    this->attackStrength = attackStrength;
}

HeroType Character::getType() const {
    return type;
}

const string & Character::getName() const {
    return name;
}

/* Returns the whole number of the health value (static_cast to int). */
int Character::getHealth() const {
    return static_cast<int>(health);
}

void Character::setHealth(double h) {
    health = h;
}

/* Reduces health value by amount passed in. */
void Character::damage(double d) {
    health = health - d;
}

/* Returns true if getHealth() returns an integer greater than 0, otherwise false */
bool Character::isAlive() const {
    if (getHealth() > 0) {
        return true;
    } else {
        return false;
    }
}