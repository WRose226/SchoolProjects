#include "AVLTree.h"

/*
insert: inserts a new node into the tree
    Returns: true if successful, false if duplicate (bool)
    Parameters:
        key (int) - integer associated with node
        value (string) - value associated with node
*/
bool AVLTree::insert(int key, string value) {
    
    // declaring pointers
    TreeNode* current = root;
    TreeNode* parentSet;
    TreeNode* balancePtr;
    bool stepThru = true;

    // if empty tree, add new node and return
    if (size == 0){
        root = new TreeNode(key, value);
        current = root;
        current->height = 0;
        current->parent = NULL;
        size++;
        return true;
    }

    // move current pointer to correct position
    while (stepThru) {

        // if duplicate, return false
        if (key == current->nodeKey) {
            return false;

        // move pointer right if key is greater than current node
        } else if (key > current->nodeKey & current->right != NULL){
            current = current->right;

        // move pointer left if key is less than current node
        } else if (key < current->nodeKey & current->left != NULL) {
            current = current->left;

        // create new right child node in case of leaf node
        } else if (key > current->nodeKey & current->right == NULL) {
            stepThru = false;
            parentSet = current;
            current->right = new TreeNode(key, value);
            current = current->right;
            current->parent = parentSet;
            current->height = 0;

        // create new left child node in case of leaf node
        } else if (key < current->nodeKey & current->left == NULL){
            stepThru = false;
            parentSet = current;
            current->left = new TreeNode(key, value);
            current = current->left;
            current->parent = parentSet;
            current->height = 0;
        }
        
    }
    
    // increment size of tree
    size++;

    // prepare balanceCheck to check balances, starting at leaf node
    balancePtr = current;
    
    // call setHeight method to set new heights on every node above new node
    setHeight(current);
    setHeight(root);
    
    return true;
}

/*
getHeight: returns the height of the tree
    Returns: height of root (int)
*/
int AVLTree::getHeight() {

    return root->height;
}

/*
getSize: returns number of nodes in tree
    Returns: size (int)
*/
int AVLTree::getSize() {

    return size;
}

/*
operator=: creates a copy of a tree
    Returns: duplicate tree (AVLTree&)
    Parameters:
        me (const AVLTree&) - tree to be copied
*/
AVLTree& AVLTree::operator=( const AVLTree& me){

    TreeNode* mePointer = me.root;
    TreeNode* current;

    if (mePointer == nullptr){
        return *this;
    }

    root = new TreeNode(mePointer->nodeKey, mePointer->value);

    current = root;
    
    equalsHelper(current, mePointer);
    

    

    return (*this);
}

AVLTree& AVLTree::equalsHelper(TreeNode* current, TreeNode* mePointer){

    if (mePointer == nullptr){
        return *this;
    }

    // copy node data
    current->height = mePointer->height;
    current->parent = mePointer->parent;
    current->left = mePointer->left;
    current->right = mePointer->right;
    
    // if mePointer left child exists, copy that into new tree's node left child
    if (mePointer->left != nullptr){
        current->left = new TreeNode(mePointer->left->nodeKey, mePointer->left->value);
        equalsHelper(current->left, mePointer->left);
    }
    
    // if mePointer right child exists, copy that into new tree's node right child
    if (mePointer->right != nullptr){
        current->right = new TreeNode(mePointer->right->nodeKey, mePointer->right->value);
        equalsHelper(current->right, mePointer->right);
    }
    

    return *this;
}

/*
operator<<: operator overload for <<. Used for printing a tree
    Returns: output stream (ostream&)
    Parameters:
        os (ostream&) - Output stream
        me (const AVLTree&) - AVLTree
*/
ostream& operator<<(ostream& os, const AVLTree& me) {

    // call print method on AVLTree me, passing in ostream
    me.print(os);
    // return ostream
    return os;
}

/*
find: determines if a specific node is contained in the tree
    Returns: true if successful, false if missing (bool)
    Parameters:
        key (int) - integer associated with node
        value (string) - value associated with node
*/
bool AVLTree::find(int key, string& value) {

    // declares current pointer
    TreeNode* current = root;

    // steps through tree until node is found or pointer reaches end of tree
    while (true){

        if (current == nullptr){
            return false;
        } else if (key > current->nodeKey){
            current = current->right;
        } else if (key < current->nodeKey){
            current = current->left;
        // if key is found, set value to given value
        } else if (key == current->nodeKey){
            value = current->value;
            return true;
        }

    }
    

}

/*
findRange: returns a vector of values contained witin the range
    Returns: vector of values contained within the range (vector<string>)
    Parameters:
        lowkey (int) - lowest value of range to search for
        highkey (int) - highest value of range to search for
*/
vector<string> AVLTree::findRange(int lowkey, int highkey) {

    // initialize vector and pointer at root
    TreeNode* current = root;
    vector<string> valueVector;

    // step through tree until node within range is found
    while (current->nodeKey < lowkey || current->nodeKey > highkey){
        if (current->nodeKey < lowkey){
            current = current->right;
        } else {
            current = current->left;
        }
        // if no node jwithin range, return
        if (current == NULL){
            return valueVector;
        }
    }

    // call recursive method to iterate through tree
    valueVector = findRangeHelper(lowkey, highkey, valueVector, current);

    return valueVector;
}

/*
findRangeHelper: recursive method to search tree for nodes within the range
    Returns: list of values associated with nodes that are within range (vector<string>)
    Parameters:
        lowkey (int) - lowest value of range
        highkey (int) - highest value of range
        valueVector (vector<string>&) - vector of values associated with nodes in range
        current (TreeNode*&) - node pointer to search through tree
*/
vector<string> AVLTree::findRangeHelper(int lowkey, int highkey, vector<string>& valueVector, TreeNode*& current) const {

    // if end of tree, return
    if (current == NULL) return valueVector;
    
    

    // recursively call to left node
    findRangeHelper(lowkey, highkey, valueVector, current->left);


    
    // if node is within range, add to vector
    if (current->nodeKey >= lowkey && current->nodeKey <= highkey){
        valueVector.push_back(current->value);
    }

    // recursively call to right node
    findRangeHelper(lowkey, highkey, valueVector, current->right);

    // return vector
    return valueVector;
}

/*
print: calls printHelper
    Returns: void
    Parameters:
        os (ostream&) - output stream
*/
void AVLTree::print(ostream& os) const {

    int depth = 0;
    TreeNode* current = root;

    // call print helper to iterate through tree and print nodes
    printHelper(os, current, depth);
}

/*
printHelper: 
    Returns: void
    Parameters:
        os (ostream&) - output stream
        current (TreeNode*&) - node pointer to iterate through tree
        depth (int) - depth of node to determine print tabbing
*/
void AVLTree::printHelper(ostream& os, TreeNode*& current, int depth) const {

    // return condition
    if (current == NULL) return;

    // call method on right child first
    printHelper(os, current->right, depth + 1);

    // represent depth of tree in print
    for (int i = 0; i < depth; i++){
        os << "    ";
    }

    // add to os the key and value of treenode
    os << current->nodeKey << ", " << current->value << ", " << endl;

    // call method on left child
    printHelper(os, current->left, depth + 1);

}

/*
setHeight: sets node heights, and calls selectRotate method if unbalance
    Returns: void
    Parameters:
        current (TreeNode*&) - node pointer to move through tree
*/
void AVLTree::setHeight(TreeNode*& current){

    bool cont = true;

    // correct node heights
    while (cont) {

        // if leaf node, height is 0
        if (current->left == nullptr & current->right == nullptr) {
            current->height = 0;

        // if only right child; height = right child's height + 1
        } else if (current->left == nullptr){
            current->height = current->right->height + 1;

        // if only left child; height = left child's height + 1
        } else if (current->right == nullptr){
            current->height = current->left->height + 1;

        // if left child's height is greater than right child's height,
        // set height to left child's height + 1
        } else if (current->left->height > current->right->height) {
            current->height = current->left->height + 1;
        // if right child's height is greater than left child's height,
        // set height to right child's height + 1;
        } else {
            current->height = current->right->height + 1;
        }

        // if unbalanced, rotateSelect
        int balance = getBalance(current);
        if (balance == 2 || balance == -2){
            rotateSelect(current);
        }

        // if top of tree, break from loop and return, else move up tree
        if (current->parent == NULL){
            cont = false;
        } else {
            current = current->parent;
        }
        
    }

}

/*
getBalance: gets balance of current node
    Returns: balance of node (int)
    Parameters:
        current (TreeNode*&) - pointer to a specific node
*/
int AVLTree::getBalance(TreeNode*& current) const {
        int balance;
        // check balance of current node and children
        // if node has both children, balance = left height - right height;
        if (current->left != nullptr & current->right != nullptr) {
            balance = current->left->height - current->right->height;
        
        // if left is nullptr, balance = 0 - right height
        } else if (current->left == nullptr & current->right != nullptr) {
            balance = 0 - (current->right->height + 1);
            

        // if right is nullptr, balance = left height
        } else if (current->right == nullptr & current->left != nullptr) {
            balance = current->left->height + 1;  

        // if both children are nullptr,
        } else {
            balance = 0;
    
        }

        return balance;
}

/*
rotateSelect: determines how tree should be rotated
    Returns: void
    Parameters:
        balancePtr (TreeNode*&) - pointer pointing to specific node
*/
void AVLTree::rotateSelect(TreeNode*& balancePtr) {
    int balance; 
    int balanceLeft = 0;
    int balanceRight = 0;

    
    // call getBalance method to check balance of node
    balance = getBalance(balancePtr);

    // check balance of left child pointer
    if (balancePtr->left != nullptr){
        balanceLeft = getBalance(balancePtr->left);
    }
    
    // check balance of right child pointer
    if ( balancePtr->right != nullptr){
        balanceRight = getBalance(balancePtr->right);
    }
        


    // conditional for DRR; SLR & SRR
    if (balance == 2 & balanceLeft == -1) {

        // Call Single Left Rotation
        SLR(balancePtr->left);
            
        // Call Single Right Rotation
        SRR(balancePtr);
            

    // conditional for DLR; SRR & SLR
    } else if (balance == -2 & balanceRight == 1) {
            
        // Call Single Right Rotation
        SRR(balancePtr->right);
            
        // Call Single Left Rotation
        SLR(balancePtr);

    // conditional for SRR
    } else if (balance == 2 & balanceLeft == 1) {

        // Call Single Right Rotation
        SRR(balancePtr);
            
    // conditional for SLR
    } else if (balance == -2 & balanceRight == -1) {

        // Call Single Left Rotation
        SLR(balancePtr);
          
    }
  
    
}

/*
SLR: Single Left Rotation
    Returns: void
    Parameters:
        problem (TreeNode*&) - pointer to problem node
*/
void AVLTree::SLR(TreeNode*& problem) {
    
    // initialize pointers
    TreeNode* hook = problem->right;
    TreeNode* grandParent = problem->parent;
    TreeNode* temp = nullptr;

    // if hook node has a left child node, set temp to that node
    if (hook->left != nullptr){
        temp = hook->left;
    }

    // change root if necessary
    if (root == problem){
        root = hook;
    }

    problem->right = nullptr;
    hook->left = problem;
    problem->parent = hook;

    // set hook as problem parent's child
    if (grandParent != nullptr){
        
        if (grandParent->left == problem){
            grandParent->left = hook;
        } else {
            grandParent->right = hook;
        }

        hook->parent = grandParent;
    } else {
        hook->parent = nullptr;
    }
    
    
    
    
    hook->height = 1;
    hook->left->height = 0;
    problem->right = nullptr;

    // if there is a temp, attach to problem node
    if (temp != nullptr){
        problem->right = temp;
        temp->parent = problem;
        setHeight(temp);
        problem->height = 1;
        hook->height = 2;
    }
    
}

/*
SRR: Single Right Rotation
    Returns: void
    Parameters:
        problem (TreeNode*&) - pointer to problem node
*/
void AVLTree::SRR(TreeNode*& problem) {

    // initialize pointers
    TreeNode* hook = problem->left;
    TreeNode* grandParent = problem->parent;
    TreeNode* temp = nullptr;

    // if hook node has a right child node, set temp to that node
    if (hook->right != nullptr){
        temp = hook->right;
    }

    // change root if necessary
    if (root == problem){
        root = hook;
    }

    problem->left = nullptr;
    hook->right = problem;
    problem->parent = hook;

    // set hook parent
    if (grandParent != nullptr){
        if (grandParent->left == problem){
            grandParent->left = hook;
        } else {
            grandParent->right = hook;
        }

        hook->parent = grandParent;
    } else {
        hook->parent = nullptr;
    }
    
    
    
    hook->height = 1;
    hook->right->height = 0;
    problem->left = nullptr;

    // if there is a temp, attach to problem node
    if (temp != nullptr){
        problem->left = temp;
        temp->parent = problem;
        setHeight(temp);
        problem->height = 1;
        hook->height = 2;
    }
  
}