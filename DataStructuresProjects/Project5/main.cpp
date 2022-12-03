#include "Trie.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using namespace std;

int main() {

    Trie myTrie;
    string nextWord;

    ifstream infile;
    infile.open("wordlist.txt");
    if (!infile){
        cout << "Couldn't open file" << endl;
        return 1;
    }

    // insert dictionary file into Trie
    while(!infile.eof()){
        getline(infile, nextWord);
        myTrie.insert(nextWord);
    }

    // cout << myTrie.count() << endl;
    // cout << myTrie.getSize() << endl;

    string userIn;
    string yesOrNo;

    while(true){

        // prompt user to enter prefix
        cout << "Please enter a word prefix (or press enter to exit): ";
        getline(cin, userIn);

        // if enter is pressed, close program
        if (userIn.length() == 0){
            break;
        } 

        cout << "There are " << myTrie.completeCount(userIn);

        // if no prefixes found, try again.
        // else, continue
        if (myTrie.completeCount(userIn) == 0){
            cout << " completions for the prefix '" << userIn << "'. Please try again." << endl << endl;
            continue;
        } else {
            cout << " completions for the prefix '" << userIn << "'. Show completions? ";
        }
        
        // receive decision from user
        cin >> yesOrNo;

        // if no, continue at beginning of loop
        if (yesOrNo == "no"){
            cout << endl;
            continue;
        }

        cout << "Completions" << endl;
        cout << "-----------" << endl;
        
        // create vector of word completions
        vector<string> myVec = myTrie.complete(userIn);

        // for loop to print out completions vector
        for (vector<string>::iterator it = myVec.begin(); it != myVec.end(); ++it) {	
		    cout << *it << endl;
	    }

        cout << endl;
    }

    
    system("pause");

}