/*
Wyatt Rose
Project 6: Hash Tables
database header File:
    Contains the definitions for database variables and methods
*/

#pragma once
#include "Record.h"
#include "HashTable.h"
#include "vector"

using namespace std;

class Database{
public:
    Database(); // constructor

    ~Database(); // destructor

    bool insert(const Record& newRecord, int& collisions); // insert record into Database

    bool remove(int key); // remove record from Database

    bool find(int uid, Record& foundRecord); // find record in database

    float alpha(); // retrieve alpha and return it

    ostream& print(ostream& os) const; // print database

    friend ostream& operator<<(ostream& os, const Database&); // operator overload for print function

    int getCollisions(){ return indexTable.collisions;} // return collisions

private:
HashTable indexTable;
vector<Record> recordStore;
};