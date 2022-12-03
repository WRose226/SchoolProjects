/*
#include "AVLTree.h"


bool AVLTree::insert(int key, string value) {

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

    // prepare balanceCheck to check balances, starting at leaf node
    balancePtr = current;
    
    // call setHeight method to set new heights on every node above new node
    setHeight(current);

    // check balances and perform proper rotations
    setBalance(balancePtr);



    size++;
    return true;
}

int AVLTree::getHeight() {

    return root->height;
    
}

int AVLTree::getSize() {

    return size;
}
/*
AVLTree& AVLTree::operator=( const AVLTree& me){



    return ;
}

ostream& operator<<(ostream& os, const AVLTree& me) {
    // call print method on AVLTree me, passing in ostream
    me.print(os);
    // return ostream
    return os;
}
/*
bool AVLTree::find(int key, string& value) {

}

vector<string> AVLTree::findRange(int lowkey, int highkey) {

}
*/
/*
void AVLTree::print(ostream& os) const {

    int depth = 0;
    TreeNode* current = root;
    printHelper(os, current, depth);
}

void AVLTree::printHelper(ostream& os, TreeNode* current, int depth) const {

    // return condition
    if (current == NULL) return;

    // call method on right child first
    printHelper(os, current->right, depth + 1);

    // represent depth of tree in print
    for (int i = 0; i < depth; i++){
        os << "    ";
    }

    // add to os the key and value of treenode
    os << current->nodeKey << ", " << current->value << ", " <<current->height << endl;

    // call method on left child
    printHelper(os, current->left, depth + 1);

}

void AVLTree::setHeight(TreeNode*& current){


    // correct node heights
    while (current != NULL) {
        
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

        int balance = getBalance(current);
        if (balance == 2 || balance == -2){
            
        }

        //if (current->height == )
        current = current->parent;
    }

}

int AVLTree::getBalance(TreeNode* current) const{
        int balance;
        // check balance of current node and children
        // if node has both children, balance = left height - right height
        if (current->left != nullptr & current->right != nullptr) {
            balance = current->left->height - current->right->height;
        
        // if left is nullptr, balance = 0 - right height
        } else if (current->left == nullptr) {
            balance = 0 - current->right->height;
            

        // if right is nullptr, balance = left height
        } else if (current->right == nullptr) {
            balance = current->left->height;  

        // if both children are nullptr,
        } else {
            balance = 0;
    
        }

        return balance;
}

void AVLTree::setBalance(TreeNode* balancePtr) {
    int balance; 
    int balanceLeft;
    int balanceRight;

    // check node balances
    while (balancePtr != nullptr) {

        balance = getBalance(balancePtr);
        balanceLeft = getBalance(balancePtr->left);
        balanceRight = getBalance(balancePtr->right);


        // conditional for DRR; SLR & SRR
        if (balance == 2 & balanceLeft == -1) {
            SLR(balancePtr);
            
            SRR(balancePtr);
            // set new height
            // return

        // conditional for DLR; SRR & SLR
        } else if (balance == -2 & balanceRight == 1) {
            SRR(balancePtr);
            
            SLR(balancePtr);
            // set new height
            // return;

        // conditional for SRR
        } else if (balance == 2 & balanceLeft == 1) {
            SRR(balancePtr);
            // set new height
            // return
        // conditional for SLR
        } else if (balance == -2 & balanceRight == -1) {
            SLR(balancePtr);
            // set new height
            // return
        }
        
        // step pointer up the tree
        balancePtr = balancePtr->parent;
    }
    
    
    
}

void AVLTree::SLR(TreeNode*& problem) {
    TreeNode* hook = problem->right;
    TreeNode* temp = nullptr;

    if (hook->left != nullptr){
        temp = hook->left;
    }

    if (root == problem){
        root = hook;
    }
    //problem parent's child is hook
    if (problem->parent->left == problem){
        hook = problem->parent->left;
    } else {
        hook = problem->parent->right;
    }
    
    hook->left = problem;
    problem->parent = hook;

    if (temp != nullptr){
        problem->left = temp;
        temp->parent = problem;
    }
    // check for left child of hook node
    // set new root if necessary
    // reset heights
    
}

void AVLTree::SRR(TreeNode*& ptr) {
    TreeNode* hook = ptr->left;

    // check for right child of hook node
    // set new root if necessary
    // reset heights
}
*/