#include <iostream>

using namespace std;

#ifndef WIZARD_H
#define WIZARD_H

#include "Character.h"

class Wizard : public Character {
  private:
    int rank;
  public:
    Wizard(const string &name, double health, double aStrength, int rank);
    int getRank() const;
    void attack(Character &opp);
};

#endif