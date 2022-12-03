/*
Wyatt Rose
Project 6: Hash Tables
Main CPP File:
    Contains the driver code
*/

#include "Database.h"
#include <iostream>

using namespace std;

// defining methods
void insertRecord(Database&);
void deleteRecord(Database&);
void searchRecord(Database&);
void printDatabase(Database&);

/*
main:   driver method to collect user input
    Returns:    int
*/
int main(){

    // initializing database
    Database studentData;

    // loop for user interface
    while (true){

        char userIn;
        
        // prompt for user input
        cout << "Would you like to (I)nsert, (D)elete a record";
        cout << ", (S)earch, (P)rint database, or (Q)uit?" << endl;

        cout << "Enter action: ";
        
        // collect user decision
        cin >> userIn;

        // call appropriate method based on user input
        if (userIn == 'I'){
            insertRecord(studentData);
        } else if (userIn == 'D'){
            deleteRecord(studentData);
        } else if (userIn == 'S'){
            searchRecord(studentData);
        } else if (userIn == 'P'){
            printDatabase(studentData);
        } else if ( userIn == 'Q'){
            cout << "Exiting.";
            break;
        } else {
            cout << endl;
            continue;
        }
    }
    

}

/*
insertRecord:   driver method to insert record into database
    Returns:    void
    Parameters:
        studentData (Database&) - holds HashTable and vector of student records
*/
void insertRecord(Database& studentData){
    int collisions;
    string lastName;
    string firstName;
    int UID;
    string year;

    // collect user input
    cout << "Inserting a new record." << endl;
    cout << "Last name: ";
    cin >> lastName;

    cout << "First name: ";
    cin >> firstName;

    cout << "UID: ";
    cin >> UID;

    cout << "Year: ";
    cin >> year;

    
    // insert new record with acquired data
    Record newStudent = Record(firstName, lastName, UID, year);
    if (studentData.insert(newStudent, collisions)){
        cout << "Record inserted" << endl;
    } else {
        cout << "Record could not be inserted" << endl;
    }

    cout << endl;
}

/*
main:   driver method to delete student record
    Returns:    void
    Parameters:
        studentData (Database&) - holds HashTable and vector of student records
*/
void deleteRecord(Database& studentData){

    int UIDIn;

    // collect user input
    cout << "UID: ";
    cin >> UIDIn;

    // remove record
    if (studentData.remove(UIDIn)){
        cout << "Record deleted" << endl;
    } else {
        cout << "Record could not be deleted" << endl;
    }

    cout << endl;
}

/*
main:   driver method to search for a student record
    Returns:    void
    Parameters:
        studentData (Database&) - holds HashTable and vector of student records
*/
void searchRecord(Database& studentData){
    // initialize blank record and UIDIn
    Record blank = Record();
    int UIDIn;

    // collect user input
    cout << "Enter UID to search for: ";
    cin >> UIDIn;
    cout << "Searching... ";

    //if record found, print record
    studentData.find(UIDIn, blank);
    cout << endl;
}

/*
main:   driver method to print records and alpha
    Returns:    void
    Parameters:
        studentData (Database&) - holds HashTable and vector of student records
*/
void printDatabase(Database& studentData){

    // print Database and alpha
    cout << "----------------------------------------------------" << endl;
    cout << studentData << endl;
    cout << "alpha: " << studentData.alpha() << endl;
    cout << "----------------------------------------------------" << endl;
}