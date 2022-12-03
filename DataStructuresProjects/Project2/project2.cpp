/*
Wyatt Rose
Project 2
main program: creates characters & simulates combat
*/

#include <iostream>
#include <string>
#include <time.h>
#include "character.h"

using namespace std;

// makes methods global
void characterCreate(Character&, Character&);
void simulateCombat(Character&, Character&);


/*-----------------------------------------------------------------
main: Calls methods to keep the code in pretty sections
    Returns: basic system exit code (int)
----------------------------------------------------------------*/
int main() {

    // Local objects that get passed to the methods
    Character character1;   // The first character the user creates
    Character character2;   // The second character the user creates

    // call method to prompt user to create characters
    characterCreate(character1, character2);

    
    // call method to simulate combat between the characters
    simulateCombat(character1, character2);
    
    // pause the system to see the results
    system("pause");
}


/*--------------------------------------------------------------------------
characterCreate: prompts the user for character data to create 2 new character objects
    Returns: void
    Parameters:
        Parameters:
        character1 (Character&) - object pointer to the first character the user created
        character2 (Character&) - object pointer to the second character the user created
---------------------------------------------------------------------------*/
void characterCreate(Character& character1, Character& character2) {

    // local variables used to construct character objects, given by user input
    string nameIn;      // the character's name
    string roleIn;      // the character's role
    int hitPointsIn;    // the character's hit points
    int attackBonusIn;  // the character's attack bonus
    int damageBonusIn;  // the character's damage bonus
    int armorClassIn;   // the character's armor class
    

    // loop twice to construct 2 characters
    for(int i = 0; i < 2; i++){

        // change console prompt depending on loop
        // prompt user for character name
        if (i == 0){
            cout << "First character name?" << endl;
        } else {
            cout << "Second character name?" << endl;
        }
            cin >> nameIn;
            cout << endl;

        // prompt user for character role
        cout << nameIn << "'s role?" << endl;
            cin >> roleIn;
            cout << endl;

        // prompt user for character hit points
        cout << nameIn << " the " << roleIn << "'s hit points?" << endl;
            cin >> hitPointsIn;
            cout << endl;

        // prompt user for character attack bonus
        cout << nameIn << " the " << roleIn << "'s attack bonus?" << endl;
            cin >> attackBonusIn;
            cout << endl;

        // prompt user for character damage bonus
        cout << nameIn << " the " << roleIn << "'s damage bonus?" << endl;
            cin >> damageBonusIn;
            cout << endl;

        // prompt user for character armor class
        cout << nameIn << " the " << roleIn << "'s armor class?" << endl;
            cin >> armorClassIn;
            cout << endl;


        // if statement to construct a character depending on the iteration of the loop
        // if first iteration, create first character object
        if(i == 0){
            character1 = Character(nameIn, roleIn, hitPointsIn,
                        attackBonusIn, damageBonusIn, armorClassIn);
            character1.print(cout);
        
        // if second iteration, create second character object
        } else {
            character2 = Character(nameIn, roleIn, hitPointsIn,
                        attackBonusIn, damageBonusIn, armorClassIn);
            character2.print(cout); 
        }
      
    }   // end of character construction loop
    
}   // end of characterCreate()


/*-----------------------------------------------------------------------------------------
simulateCombat: simulate combat between two characters
    Returns: void
    Parameters:
        character1 (Character&) - object pointer to the first character the user created
        character2 (Character&) - object pointer to the second character the user created
------------------------------------------------------------------------------------------*/
void simulateCombat(Character& character1, Character& character2){

    // Local variables
    bool noWinner = true;       //determines when to escape the loop and stop the game
    bool switchTurns = true;    //switches between character1 and character2's turns

    // display to console "Simulated Combat"
    cout << "Simulated Combat:" << endl;
    cout << endl;

    // random time seed for dice roll in attack function
    srand(time(NULL));

    // while there is no winner, continue attacking
    while(noWinner){
        if (switchTurns == true){
            cout << character1.getName() <<  " attacks!" << endl;
            character1.attack(character2);

            switchTurns = false;
        } else {
            cout << character2.getName() << " attacks!" << endl;
            character2.attack(character1);

            switchTurns = true;
        }


        // check if either character is dead
        // if character is dead, declare winner and exit loop
        if (character1.getHealth() <= 0){
            cout << character2.getName() << " wins!" << endl;
            noWinner = false;
        } else if (character2.getHealth() <= 0) {
            cout << character1.getName() << " wins!" << endl;
            noWinner = false;
        }

    } // end of noWinner while loop
    

} // end of simulateCombat()
