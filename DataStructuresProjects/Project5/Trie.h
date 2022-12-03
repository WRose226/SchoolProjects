#pragma once

#include <iostream>
#include <exception>
#include <vector>

using namespace std;

class Trie {

public:
    bool insert(string);            // stores words in the trie, rejects duplicates

    int count();                    // returns number of words in the trie

    int getSize();                  // returns number of nodes in the trie

    bool find(string);              // determines if a word is present in the trie

    int completeCount(string);      // returns number of words in the trie matching given prefix

    vector<string> complete(string);// returns vector of words that begin with given prefix

private:

    class TrieNode {
    public:
        bool eow;                 // end of word
        TrieNode* charArray[26];  // Array of pointers representing characters

        // Initialize array and eow inside of TrieNode
        TrieNode(){
            eow = false;
            
            for (int i = 0; i < 26; i++){
                charArray[i] = nullptr;
            }

        }

        ~TrieNode();

    };

    TrieNode* root = nullptr;       // first node in trie
    int nodeCount = 0;              // number of nodes in trie
    int wordCount = 0;              // number of words in trie
    int completeCounter = 0;        // number of words that begin with prefix

    void countHelper(TrieNode* follower);   // recursive method to count number of words that start with prefix

    // recursive method to return vector of words that start with prefix
    vector<string> completeHelper(vector<string>& completions, TrieNode* follow, string prefix);

};