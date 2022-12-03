/*
Wyatt Rose
Project 3
Sequence CPP File:
    Contains Sequence Object Functions
*/

#include "sequence.h"
#include <exception>

/*
Sequence:   Constructor for Sequence object.
    Returns:    void
    Paramaters:     
        sz (size_type) - Size of Sequence
*/
Sequence::Sequence( size_type sz )
{
    head = tail = NULL; // initialize head and tail as NULL
    numElts = sz;       // define numElts as size paramater
    SequenceNode* current = head; // current pointer

    // loop for creating sz number of nodes
    for (int i = 0; i < sz; i++){

        // for first iteration, define head and tail as new node
        if (head == NULL) {
            head = tail = new SequenceNode(0);
            current = head;
        
        // for rest of loop, create new nodes and define next and previous pointers
        } else {
            
            current->next = new SequenceNode(0);
            current = current->next;
            current->prev = tail;
            tail = current;
        }
    }

}

/*
Sequence: copy constructor for Sequence
    Returns:    void
    Paramaters:
        s (const Sequence&) - 
*/
Sequence::Sequence( const Sequence& s )
{

    //create 
    head = new SequenceNode(s.head->elt);
    
    // node pointers for each sequence
    SequenceNode* sPointer = s.head;
    SequenceNode* current = head;
    SequenceNode* prevSet = head;


    // move pointer through sequence and create a copy while
    // there are still nodes to be copied
    while(sPointer->next != NULL){

        //  increment s sequence pointer
        sPointer = sPointer->next;

        //  next sequence node with s sequence element
        current->next = new SequenceNode(sPointer->elt);
        // increment current pointer
        current = current->next;

        //  set prev pointer and increment pointer
        current->prev = prevSet;
        prevSet = prevSet->next;
    }

    // set tail to current node and copy numElts
    tail = current;
    numElts = s.numElts;
}


/*
~Sequence: Sequence destructor
    Returns:    void
*/
Sequence::~Sequence()
{
    // call clear method to destruct Sequence
    clear();
}


/*
operator=: Operator overload for =. Sets one sequence equal
           to another sequence.
    Returns:    Sequence address (Sequence&)
    Paramaters:
        s (const Sequence&) - 
*/
Sequence& Sequence::operator=( const Sequence& s )
{

    // call clear method to erase sequence
    clear();

    //create
    head = new SequenceNode(s.head->elt);

    // node pointers for each sequence
    SequenceNode* sPointer = s.head;
    SequenceNode* current = head;
    SequenceNode* prevSet = head;

    
    

    // move pointer through sequence and create a copy while
    // there are still nodes to be copied
    while(sPointer->next != NULL){

        //  increment s sequence pointer
        sPointer = sPointer->next;

        //  next sequence node with s sequence element
        current->next = new SequenceNode(sPointer->elt);
        // increment current pointer
        current = current->next;

        //  set prev pointer and increment pointer
        current->prev = prevSet;
        prevSet = prevSet->next;
    }

    // set tail to current node and copy numElts
    tail = current;
    numElts = s.numElts;

    return(*this);
}


/*
operator[]: operator overload for []. Modifys element in 
            specified position
    Returns:    element of position (value_type&)
    Paramaters:
        position (size_type) - Position in the sequence
*/
Sequence::value_type& Sequence::operator[]( size_type position )
{

    // create current pointer at head
    SequenceNode* current = head;

    // increment pointer to position
    for(int i = 0; i < position; i++){
        current = current->next;
    }

    // return current element
    return current->elt;
}


/*
push_back:  Adds node to end of sequence
    Returns:    void
    Paramaters:
        value (const value_type&) - value of the node
*/
void Sequence::push_back( const value_type& value )
{
    
    // create pointers
    SequenceNode* current = head;
    SequenceNode* prevSet = head;

    // if no elements, create new node with paramater value
    if (numElts == 0){

        current = head = tail = new SequenceNode(value);
        current->next = NULL;
        current->prev = NULL;

    // add value to end of sequence
    } else {

        // move to end of sequence
        while (current->next != NULL){
            current = current->next;
        }

        // create new node, set both prevs and nexts and tail
        prevSet = current;
        current->next = new SequenceNode(value);
        current = current->next;
        current->next = NULL;
        current->prev = prevSet;
        prevSet->next = current;
        tail = current;
    }
    
    // increment number of elements
    numElts++;
}


/*
pop_back: removes last element of sequence
    Returns:    void
*/
void Sequence::pop_back()
{

    // if no elements, throw exception
    if (numElts == 0){
        throw exception();
    }

    // create pointers
    SequenceNode* current = head;
    SequenceNode* prevSet = head;

    // set current to tail
    current = tail;

    // if there is more than 1 node
    if (current->prev != NULL){
        prevSet = current->prev;
        tail = prevSet;
        prevSet->next = NULL;

    // in case of 1 node, set head and tail to NULL
    } else {
        head = NULL;
        tail = NULL;
    }
    
    // delete current node
    delete current;

    // decrement number of elements
    numElts--;
}


/*
insert: inserts a new node into the sequence
    Returns:    void
    Paramaters:
        position (size_type) - position of new node
        value (value_type) - value of new node element
*/
void Sequence::insert( size_type position, value_type value )
{

    // if invalid position, throw exception
    if (position > numElts - 1 || position < 0){
        throw exception();
    }

    // create pointers and set them to head
    SequenceNode* current = head;
    SequenceNode* prevSet = head;

    // if first position, create new node at beginning
    if (position == 0){
        prevSet = new SequenceNode(value);
        prevSet->next = head;
        current->prev = prevSet;
        head = prevSet;
        
    } else {

        // move pointer to position
        for (int i = 0; i < position; i++){
            current = current->next;
        }

        // create new node and set next and previous pointers to proper nodes
        prevSet = current->prev;
        SequenceNode* newNode = new SequenceNode(value);
        prevSet->next = newNode;
        current->prev = newNode;
        newNode->prev = prevSet;
        newNode->next = current;
    }

    // increment number of elements
    numElts++;
}


/*
front:  returns first element in sequence
    Returns:    first element (value_type&)
*/
const Sequence::value_type& Sequence::front() const
{

    // if no nodes, throw exception
    if (numElts < 1){
        throw exception();
    }

    // return first node element
    return head->elt;
}


/*
back:   returns last element in sequence
    Returns:    last element (value_type&)
*/
const Sequence::value_type& Sequence::back() const
{

    // if no nodes, throw exception
    if (numElts < 1){
        throw exception();
    }

    // return last node element
    return tail->elt;
}


/*
empty: returns wether sequence is empty or not
    Returns: empty or not (bool)
*/
bool Sequence::empty() const
{
    // if no head element, sequence is empty
    if(head == NULL){
        return true;
    }

    // sequence is not empty
    return false;
}


/*
size:   returns number of elements in sequence
    Returns:    Number of Elements (size_type)
*/
Sequence::size_type Sequence::size() const
{
    // return number of elements
    return numElts;
}


/*
clear:  deletes entire sequence
    Returns:    void
*/
void Sequence::clear()
{
    // if no elements, return
    if (numElts < 1){
        return;
    }

    // create pointers
    SequenceNode* destroyer = head;
    SequenceNode* current = head;

    // step pointers through sequence and delete nodes
    while(current->next != NULL){
        current = current->next;
        delete destroyer;
        destroyer = current;
    }

    // delete last node
    delete destroyer;

    // set head and tail to NULL, numElts to 0
    head = NULL;
    tail = NULL;
    numElts = 0;

}


/*
erase:  deletes a specific node in sequence
    Returns:    void
    Paramaters:
        position (size_type) -  position of node in sequence
        count (size_type) -     number of nodes to be deleted
*/
void Sequence::erase( size_type position, size_type count )
{

    // if invalid position and count combination, throw exception
    if (numElts == 0 || position > numElts - 1 || position < 0 ||
                                     position + count > numElts){
        throw exception();
    }

    // create pointers, set all to head
    SequenceNode* prevSet = head;
    SequenceNode* current = head;
    SequenceNode* destroyer = head;

    // edge case position == 0
    if (position == 0){

        // delete count nodes
        for (int i = 0; i < count; i++){
        destroyer = current;
        current = current->next;
        delete destroyer;
        }

        // seat head to current, and current's prev pointer to NULL
        head = current;
        current->prev = NULL;
    
    } else {
        
        // set pointer to start position
        for(int j = 0; j < position; j++){
            current = current->next;
        }

        // set prevSet pointer before start position
        prevSet = current->prev;

        // delete count nodes
        for (int k = 0; k < count; k++){
            destroyer = current;
            current = current->next;
            delete destroyer;
        }

        // if last node is deleted
        if ( position + count == numElts){

            tail = prevSet;
            prevSet->next = NULL;
        
        // on case of deletion of middle nodes
        } else {
            
            // set next and previous
            prevSet->next = current;
            current->prev = prevSet;
        }
    }
    
    // decrease numElts by count
    numElts -= count;
}

/*
print:  transfers sequence elements to ostream
    Returns:    void
    Paramaters:
        os (ostream&) - output stream
*/
void Sequence::print( ostream& os ) const
{

    // create current pointer
    SequenceNode* current = head;

    // start sequence
    os << "<";
    
    // step pointer through sequence
    while (current != NULL){

        // format sequence beautifully
        if (current->next == NULL){
            os << current->elt;
        } else {
            os << current->elt << ", ";
        }

        // increment pointer
        current = current->next;
    }

    // close sequence
    os << ">";

}

/*
operator<<: operator overload for <<. Used for printing a Sequence.
    Returns:    output stream (ostream&)
    Paramaters:
        os (ostream&) - Output stream
        s (Sequence&) - sequence
*/
ostream& operator<<( ostream& os, Sequence& s )
{
    // call print method on Sequence s, passing in output stream
    s.print(os);
    // return output stream
    return os;
}