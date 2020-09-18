#include <iostream>

using namespace std;

#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character {
  private:
    string allegiance;
  public:
    Warrior(const string &name, double health, double aStrength, string allegiance);
    string getAllegiance() const;
    void attack(Character &opp);
};

#endif