/*
Wyatt Rose; Project1; Simulating Dice Rolls

Global Variables:
    arrayMax:  assign a size to the array that stores the dice roll data
*/

#include <iostream>
#include <time.h>
#define arrayMax 13

using namespace std;

/*
main: simulates dice rolls and prints out data

Returns:  basic program exit (int)
*/

int main() {

    // local variables
    int userValue;

    // create array
    int array[arrayMax];

    // pseudo random number generator with changing seed
    srand(time(NULL));


    // prompt input from user
    cout << "How many rolls? ";
    cin >> userValue;
    cout << "Simulating " << userValue << " rolls..." << endl;
    cout << "Results:" << endl;


    // initialize array with zeros
    for(int init = 0; init < arrayMax; init++){
        array[init]=0;
    }
    
    // simulate 2 dice rolls, store result in array
    for(int i = 0; i < userValue; i++){
        int randNum1 = (rand() %6) + 1;
        int randNum2 = (rand() %6) + 1;
        int randTotal = randNum1 + randNum2;
        array[randTotal] = array[randTotal] + 1;
    }

    // print out array data to console
    for(int j = 2; j < arrayMax; j++){
        cout << j << " was rolled " << array[j] << " times" << endl;
    }


    system("pause");
}