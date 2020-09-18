#include <iostream>

using namespace std;

#include "Character.h"
#include "Wizard.h"

Wizard::Wizard(const string &name, double health, double aStrength, int rank)
               : Character(WIZARD, name, health, aStrength),
               rank(rank) { }

int Wizard::getRank() const {
    return rank;
}

void Wizard::attack(Character &opponent) {
    if (opponent.getType() == WIZARD) {
        Wizard &opp = dynamic_cast<Wizard &>(opponent);
        
        double damageDealt = attackStrength * (static_cast<double>(getRank()) / opp.getRank()); 
        // if (opp.getType() == type) {
            cout << "Wizard " << name << " attacks " << opp.getName() << " --- POOF!!" << endl;
            cout << opp.getName() << " takes " << damageDealt << " damage." << endl;
            opp.damage(damageDealt);
        // } else {
        //     cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl;
        //     cout << opponent.getName() << " takes " << attackStrength << " damage." << endl;
        //     opponent.damage(attackStrength);
        // }
    } else {
        cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl;
        cout << opponent.getName() << " takes " << attackStrength << " damage." << endl;
        opponent.damage(attackStrength);
    }
}