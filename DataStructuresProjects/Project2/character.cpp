/*
Wyatt Rose
Project 2
character CPP file:
    contains constructors, print, attack and damage functions
    and getters and setters for Character object data
*/

#include "character.h"
#include <iostream>
#include <time.h>


// Default constructor for Character
Character::Character() {

    name = "";
    role = "";
    hitPoints = 0;
    attackBonus = 0;
    damageBonus = 0;
    armorClass = 0;

}


// Parameterized constructor for Character
Character::Character(string newName, string newRole,
                 int newHP, int newAB, int newDB, int newAC) {

    name = newName;
    role = newRole;
    hitPoints = newHP;
    attackBonus = newAB;
    damageBonus = newDB;
    armorClass = newAC;

}


// Pretty print a character object
void Character::print(ostream& os){
    os << "Character summary" << endl;
    os << "-----------------" << endl;
    os << name << " the " << role << endl;
    os << "Hit Points: " << hitPoints << endl;
    os << "Attack Bonus: " << attackBonus << endl;
    os << "Damage Bonus: " << damageBonus << endl;
    os << "Armor Class: " << armorClass << endl;
    os << endl;
}


// determines if the attack hits or misses
// if attack hits, calls damage function
void Character::attack(Character &otherCharacter){

    // calculate attack with dice roll and attack bonus
    int rollDie = (rand() % 20) + 1;
    int attack = rollDie + attackBonus;

    // if attack >= other character's armor class, call damage function
    // else determine MISS
    if (attack >= otherCharacter.getArmorClass()){
        cout << "Attack roll: " << rollDie << " + " << attackBonus << " = " 
                                            << attack << " --> HIT!" << endl;
        damage(otherCharacter);
    } else {
        cout << "Attack roll: " << rollDie << " + " << attackBonus << " = "
                                             << attack << " --> MISS!" << endl;
        cout << endl;
    }

} // end of attack function


// rolls a dice and determines the damage done by one character to the other
void Character::damage(Character &otherCharacter){

    // Local variables
    int rollDie = (rand() % 10) + 1;        // roll dice to determine base damage
    int damage = rollDie + attackBonus;     // determine total damage

    // print to console damage equation
    cout << "Damage: " << rollDie << " + " << attackBonus << " = " << damage << endl;
    
    // set new health for damaged character
    int newHealth = otherCharacter.getHealth() - damage;
    otherCharacter.setHealth(newHealth);

    // print to console damaged character's remaining health
    cout << otherCharacter.getName() << " has " << otherCharacter.getHealth() << 
                                        " hit points remaining" << endl;
    cout << endl;

} // end of damage function


// Getters
int Character::getHealth(){
    return hitPoints;
}

int Character::getAttackBonus(){
    return attackBonus;
}

int Character::getArmorClass(){
    return armorClass;
}

string Character::getName(){
    return name;
}

string Character::getRole(){
    return role;
}

// Setters
void Character::setHealth(int newHitPoints){
    hitPoints = newHitPoints;
}