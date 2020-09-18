#include <iostream>
#include <string>

using namespace std;

#include "Character.h"
#include "Elf.h"

Elf::Elf(const string &name, double health, double aStrength, string family)
         : Character(ELF, name, health, aStrength), 
           family(family) { }
         
string Elf::getFamily() const {
    return family;
}

void Elf::attack(Character &opponent) {
    double damageDealt = (health / MAX_HEALTH) * attackStrength;
    if (opponent.getType() == ELF) {
        
        Elf &opp = dynamic_cast<Elf &>(opponent);
        
        //double damageDealt = (getHealth() / MAX_HEALTH) * attackStrength;
    
        if (opp.getFamily() == family ) {
            cout << "Elf " << name << " does not attack Elf " << opp.getName() << "." << endl;
            cout << "They are both members of the " << getFamily() << " family." << endl;
        } else {
            cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
            cout << opponent.getName() << " takes " << damageDealt << " damage." << endl;
            opponent.damage(damageDealt);
        }
    } else {
        cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl;
        cout << opponent.getName() << " takes " << damageDealt << " damage." << endl;
        opponent.damage(damageDealt);
    }
}