/*
Wyatt Rose
Project 2
Character header file
*/
#pragma once
#include <string>

using namespace std;

/*---------------------------------------------------------------------
Character (Class): sets up the Character class using private variables
                    and public constructors, functions,
                    getters and setters
--------------------------------------------------------------------*/
class Character {
private:
    string name;
    string role;
    unsigned int hitPoints;
    int attackBonus;
    int damageBonus;
    int armorClass;

public:
    // Default Constructor
    Character();

    //Parameterized constructor
    Character(string, string, int, int, int, int);

    // Pretty Print
    void print(ostream&);

    // attack function
    void attack(Character &otherCharacter);

    // damage function
    void damage(Character &otherCharacter);

    // Getters
    int getHealth();

    int getAttackBonus();

    int getArmorClass();

    string getName();

    string getRole();

    // Setters
    void setHealth(int);
};