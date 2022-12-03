/*
Wyatt Rose
Project 6: Hash Tables
Database CPP File:
    Contains the implementation of database
*/

#include "Database.h"
#include "HashTable.h"

// constructor and destructor
Database::Database(){}
Database::~Database(){}

/*
insert:   method to insert record into database
    Returns:    bool
    Parameters:
        newRecord (Record&) - Record to be inserted into database
        collisions (int&) - number of collisions during insertion
*/
bool Database::insert(const Record& newRecord, int& collisions){

    int index = 0;
    // Check to make sure the UID is not already in the HashTable.
    if (indexTable.find(newRecord.getUID(), index)){
        return false;

    // If not, insert the Record into the recordStore, and
    } else {
        
        // Insert the UID and the slot the Record occupies in the recordStore into the HashTable
        int key = newRecord.getUID();
        int index = recordStore.size();
        collisions = 0;
        indexTable.insert(key, index, collisions);

        recordStore.push_back(newRecord);
    }

    return true;
}

/*
remove:   method to remove record from database
    Returns:    bool
    Parameters:
        key (int) - key to be remove from HashTable and recordStore
*/
bool Database::remove(int key){

    int index = 0;
    //If there is a record with the given key in the Database, it is deleted and the function returns true 
    if (indexTable.find(key, index)){

        // replace record @ index with last record
        recordStore[index] = recordStore[recordStore.size()-1];

        // update index in slot that changed
        indexTable.setIndex(index, recordStore.size()-1);
        
        // remove last record from vector
        recordStore.pop_back();

        // remove record from hash table
        indexTable.remove(key);
        
        return true;
    // otherwise the function returns false
    } else return false;

}

/*
find:   method to search record in database
    Returns:    bool
    Parameters:
        uid (int) - Record to be searched in HashTable
        foundRecord (Record&) - Record object to be updated with found record to print
*/
bool Database::find(int uid, Record& foundRecord){
    int index = 0;
    // if record is found, update foundRecord and print
    if(indexTable.find(uid, index)) {
        foundRecord = recordStore[index];
        cout << " record found (" << indexTable.getCollisions() << " collisions during search)" << endl;
        cout << "------------------------------------------------" << endl;
        cout << foundRecord << endl;
        cout << "------------------------------------------------" << endl;
        return true;
    // if record is not found, print to console
    } else {
        cout << " record not found" << endl;
    }

    return false;
}

/*
alpha:  calls indexTable.alpha() to retrieve alpha
    Returns:    float
*/
float Database::alpha(){
    return indexTable.alpha();
}

/*
print: prints database
    Returns: ostream&
    Parameters:
        os (ostream&) - output stream
*/
ostream& Database::print(ostream& os) const {

    // iterates through HashTable
    for(int i = 0; i<MAXHASH; i++){
        // if HashTable slot is occupied with record
        if ((indexTable.getSlots()+i)->isNormal()){
            // update index and print records in HashTable
            int index = (indexTable.getSlots()+i)->getIndex();
            os << "HashTable Slot: " << i << ", recordStore slot " << index << " -- " << recordStore[index] << endl;
        }
    }
    
    return os;
}

/*
operator<<: operator overload for <<. Used for printing the database
    Returns: output stream (ostream&)
    Parameters:
        os (ostream&) - Output stream
        d (const AVLTree&) - database to be printed
*/
ostream& operator<<(ostream& os, const Database& d){
    d.print(os);
    return os;
}