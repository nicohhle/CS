#include <iostream>
#include <string>

using namespace std;

#include "Character.h"
#include "Warrior.h"

Warrior::Warrior(const string &name, double health, double aStrength, string allegiance)
        : Character(WARRIOR, name, health, aStrength),
        allegiance(allegiance) { }

string Warrior::getAllegiance() const {
    return allegiance;
}

void Warrior::attack(Character &opponent) {
    if (opponent.getType() == WARRIOR) {
        Warrior &opp = dynamic_cast<Warrior &>(opponent);
        
        if (opp.getAllegiance() == allegiance) {
            cout << "Warrior " << name << " does not attack Warrior " << opp.getName() << "." << endl;
            cout << "They share an allegiance with " << allegiance << "." << endl; 
        } else {
            cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!" << endl;
            cout << opponent.getName() << " takes " << (health / MAX_HEALTH) * attackStrength << " damage." << endl;
            opponent.damage((health / MAX_HEALTH) * attackStrength);
        }
    } else {
        cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!" << endl;
        cout << opponent.getName() << " takes " << (health / MAX_HEALTH) * attackStrength << " damage." << endl;
        opponent.damage((health / MAX_HEALTH) * attackStrength);
    }
}

