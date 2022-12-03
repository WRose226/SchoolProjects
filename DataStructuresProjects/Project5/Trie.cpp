#include "Trie.h"



/*
insert: Inserts a new word into the trie. Duplicates not allowed
    Returns:    true if word inserted, false if word cant be inserted (bool)
    Parameters:
        newWord (string) - word to be inserted into trie
*/
bool Trie::insert(string newWord){

    TrieNode* current = root;
    int NWLength = newWord.length();

    // if no root, create root
 if (root == nullptr){
        root = new TrieNode();
        nodeCount++;
        current = root;
    }

    // iterate through characters of newWord
    for (auto &ch : newWord){

        // if no pointer exists for current letter, create new pointer
        // else, follow the pointer
        if(current->charArray[(int)ch - 97] == nullptr){
            current->charArray[(int)ch - 97] = new TrieNode();
            current = current->charArray[(int)ch - 97];
            NWLength--;
            nodeCount++;
        } else {
            current = current->charArray[(int)ch - 97];
            NWLength--;
        }


        // if this word already exists, return false
        // if end of word, set eow to true
        if (NWLength == 0){
            if (current->eow == true){
                return false;
            } else {
                current->eow = true;
                wordCount++;
                return true;
            }
        }
        
    }

}

/*
count: returns number of words in trie
    Returns: number of words in trie (int)
*/
int Trie::count(){

    return wordCount;
}

/*
getSize: returns total number of nodes in trie
    Returns: total number of nodes in trie (int)
*/
int Trie::getSize(){

    return nodeCount;
}

/*
find: finds a given word in the trie
    Returns: true if word is found, false if word isnt found (bool)
    Parameters:
        findWord (string) - word to be found in trie
*/
bool Trie::find(string findWord){

    TrieNode* current = root;
    int FWLength = findWord.length();

    // iterate through characters of newWord
    for (auto &ch : findWord){

        // if no pointer exists for current letter, return false
        // else, follow the pointer
        if(current->charArray[(int)ch - 97] == nullptr){
            return false;
        } else {
            current = current->charArray[(int)ch - 97];
            FWLength--;
        }


        // if the word exists, return true
        if (FWLength == 0 && current->eow == true){
            return true; 
        }
    }

    return false;
}

/*
completeCount: counts number of words that begins with given prefix
    Returns: number of words that begins with given prefix (int)
    Parameters:
        prefix (string) - other words checked to begin with this string
*/
int Trie::completeCount(string prefix){

    completeCounter = 0;
    TrieNode* current = root;
    int prefixLength = prefix.length();

    // iterate through characters of newWord
    for (auto &ch : prefix){

        // if no pointer exists for current letter, return 0
        // else, follow the pointer
        if(current->charArray[(int)ch - 97] == nullptr){
            return 0;
        } else {
            current = current->charArray[(int)ch - 97];
            prefixLength--;
        }


        // when the pointer is at the correct node, call the recursive helper method
        if (prefixLength == 0){
            countHelper(current); 
        }
    }

    return completeCounter;
}

/*
countHelper: helps the completeCount method through recursion
    returns: void
    Parameters:
        follow (TrieNode*) - TrieNode pointer to traverse through the Trie
*/
void Trie::countHelper(TrieNode* follow) {

    // step through the array, follow pointers
    for (int i = 0; i < 26; i++){
        if (follow->charArray[i] != nullptr){
            TrieNode* newFollow = follow->charArray[i];
            countHelper(newFollow);
        }
    }

    // increment counter if node is end of word
    if (follow->eow == true){
        completeCounter++;
        return;
    }

}

/*
complete:   auto-complete function
    Returns: vector of strings containing all words that begin with given input string (vector<string>)
    Parameters:
        prefix (string) - other words checked to begin with this string
*/
vector<string> Trie::complete(string prefix){
    
    vector<string> completions;
    TrieNode* current = root;
    int prefixLength = prefix.length();

    // iterate through characters of newWord
    for (auto &ch : prefix){

        // if no pointer exists for current letter, return empty vector
        // else, follow the pointer
        if(current->charArray[(int)ch - 97] == nullptr){
            return completions;
        } else {
            current = current->charArray[(int)ch - 97];
            prefixLength--;
        }


        // When the pointer is at the correct node, call the recursive helper method
        if (prefixLength == 0){
            completions = completeHelper(completions, current, prefix); 
        } 
    }

    return completions;
}

/*
completeHelper: recursive method to help the complete method 
    Returns: vector of strings containing the words that begin with given input string (vector<string>)
    Parameters:
        completions (vector<string>&) - vector of words that begin with given prefix
        follow (TrieNode*) - pointer to follow to next node
        prefix (string) - string of characters the pointer builds on as it moves through the Trie
*/
vector<string> Trie::completeHelper(vector<string>& completions, TrieNode* follow, string prefix){

    // if the end of the word, add it to the vector
    if (follow->eow == true){
        completions.push_back(prefix);
    }
    
    // step through the array, recursively call this method on the pointers
    for (int i = 0; i < 26; i++){
        if (follow->charArray[i] != nullptr){
            TrieNode* newFollow = follow->charArray[i];
            completions = completeHelper(completions, newFollow, prefix + (char)(i + 97));
        }
    }
    
    return completions;
}