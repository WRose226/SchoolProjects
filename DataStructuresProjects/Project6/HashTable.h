/*
Wyatt Rose
Project 6: Hash Table
HashTable header File:
    Contains the definitions for HashTable variables and methods
*/

#pragma once
#include "Slot.h"
#define MAXHASH 20

using namespace std;

class HashTable{
public:
    int collisions; // 

    HashTable(); // constructor

    ~HashTable(); // destructor

    bool insert(int key, int index, int& collisions); // insert data into slot

    bool remove(int key); // remove slot from array

    bool find(int key, int& index); // find slot in array

    float alpha(); // get alpha

    int getCollisions(){ return collisions;} //get collisions

    const Slot* getSlots() const {return slots;} // slots getter

    void setIndex(int, int); // set new index for slot after deletion
private:
    Slot slots[MAXHASH]; // array of slots to make up the hashtable
    int probeSeq[MAXHASH - 1]; // probe sequence
    
};