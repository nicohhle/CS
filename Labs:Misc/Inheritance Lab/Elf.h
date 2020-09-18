#include <iostream>

using namespace std;

#ifndef ELF_H
#define ELF_H

#include "Character.h"

class Elf : public Character {
  private:
    string family;
  public:
    Elf(const string &name, double health, double aStrength, string family);
    string getFamily() const;
    void attack(Character &opp);
};

#endif