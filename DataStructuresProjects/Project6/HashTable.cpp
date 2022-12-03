/*
Wyatt Rose
Project 6: Hash Tables
HashTable CPP File:
    Contains the implementation of HashTable
*/

#include "HashTable.h"
#include "hashfunction.h"
#include <chrono>
#include <random>
#include <algorithm>

/*
HashTable:   Constructor to initialize probeSequence
*/
HashTable::HashTable(){
    
    // initialize probing array
    for (int i = 0; i < MAXHASH-1; i++) {
        probeSeq[i] = i+1;
    }

    // CITED https://www.cplusplus.com/reference/algorithm/shuffle/
    // Shuffle probing array
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(begin(probeSeq), end(probeSeq), default_random_engine(seed));

    //print probe offsets
    //for (int i = 0; i < MAXHASH-1; i++){
    //    cout << offset[i] << ", ";
    //}
    
}

/*
~HashTable:   destructor method
*/
HashTable::~HashTable(){}

/*
insert:   insert key and index into hashtable
    Returns:    bool
    Parameters:
        key (int) - key to inserted into HashTable
        index (int) - index to be inserted into HashTable
        collisions (int&) - updates collisions during insertion
*/
bool HashTable::insert(int key, int index, int& collisions){

    int home = jsHash(key) % MAXHASH;

    // if duplicate, return false
    if (slots[home].getKey() == key){
        return false;
    }
    
    // if home slot is empty, insert key and index
    if (slots[home].isEmptySinceStart()){
        slots[home].setKey(key);
        slots[home].setIndex(index);
        slots[home].setType();
        return true;
    }

    // home slot not empty, pseudo random probe through entire hashtable
    for (int j = 0; j < MAXHASH; j++){
        int probe = (home + probeSeq[collisions]) % MAXHASH;

        // if slot key is duplicate, return false
        if (slots[probe].getKey() == key){
            return false;

        // if slot is empty, insert data & return true
        } else if (slots[probe].isEmptySinceStart()){
            slots[probe].setKey(key);
            slots[probe].setIndex(index);
            slots[probe].setType();
            return true;

        // else increment collisions
        } else collisions++;
    }

    // hashtable full, return false
    return false;

}

/*
remove:   method to remove record from HashTable
    Returns:    bool
    Parameters:
        key (int) - key to be removed from HashTable
*/
bool HashTable::remove(int key){

    collisions = 0;
    // compute home position
    int home = jsHash(key) % MAXHASH;

    // if slot is occupied in home position and key matches, kill and return
    if (slots[home].isNormal() && slots[home].getKey() == key){
        slots[home].kill();
        return true;
    }

    
    for (int j = 0; j < MAXHASH; j++){
        // compute probe slot
        int probe = (home + probeSeq[collisions]) % MAXHASH;

        // if probe slot key is a match, kill and return
        if (slots[probe].isNormal() && slots[probe].getKey() == key){
            slots[probe].kill();
            return true;
        // else increment collisions
        } else collisions++;
    }

    //slot empty, return false
    return false;
}

/*
find:   method to find record in HashTable
    Returns:    bool
    Parameters:
        key (int) - key to be found in HashTable
        index (int&) - index to be updated from slot with matching key
*/
bool HashTable::find(int key, int& index){

    collisions = 0;
    // compute home position
    int home = jsHash(key) % MAXHASH;

    // check if key is at home position
    if (slots[home].getKey() == key){
        // update index to the slot's index and return
        index = slots[home].getIndex();
        return true;

    // if key is not in home, and slot is filled, check through probe sequence
    } else if (slots[home].getKey() != key && slots[home].isNormal()){

        // iterate through probe sequence
        for (int j = 0; j < MAXHASH; j++){
            // compute probe slot
            int probe = (home + probeSeq[collisions]) % MAXHASH;

            // if slot key is found, update index & return true
            if (slots[probe].getKey() == key){
                index = slots[probe].getIndex();
                return true;

            // else increment collisions
            } else collisions++;
        }
    }

    
    // not found, return false
    return false;
}

/*
setIndex:   method to update index of slot during deletion
    Returns:    void
    Parameters:
        index (int) - index to be updated to
        lastRecord (int) - last index to be found and updated
*/
void HashTable::setIndex(int index, int lastRecord){

    // run through slots until slot corresponding to last record in the vector is found
    for (Slot i : slots){
        if (i.getIndex() == lastRecord){
            // set index to new position
            i.setIndex(index);
            break;
        }
    }


}

/*
alpha:   returns alpha
    Returns:    float
*/
float HashTable::alpha(){

    int occupied = 0;
    // iterate through slots, increment if slot is occupied
    for (Slot i : slots){
        if (i.isNormal()){
            occupied++;
        }
    }

    // return float of alpha
    return (float)occupied/MAXHASH;
}

