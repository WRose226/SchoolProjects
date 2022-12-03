#pragma once

#include <iostream>
#include <exception>
#include <vector>

using namespace std;

class AVLTree {

public:
    bool insert(int key, string value);

    int getHeight();

    friend ostream& operator<<(ostream& os, const AVLTree& me);

    AVLTree& operator=( const AVLTree& me);

    int getSize();

    bool find(int key, string& value);

    vector<string> findRange(int lowkey, int highkey);

    void print(ostream&) const;


private:

    class TreeNode {
    public:
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        int height;
        string value;
        int nodeKey;
        

        TreeNode(){
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            height = 0;
        }

        TreeNode(int k, string val){
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            height = 0;
            value = val;
            nodeKey = k;
        }

        ~TreeNode() {};

    };

    //MEMBER DATA
    TreeNode* root;
    int size = 0;

    AVLTree& equalsHelper(TreeNode* current, TreeNode* mePointer);

    vector<string> findRangeHelper(int lowkey, int highkey, vector<string>& nodes, TreeNode*& current) const;

    void printHelper(ostream& os, TreeNode*& current, int depth) const;

    void setHeight(TreeNode*& current);

    void rotateSelect(TreeNode*& current);
    
    void SLR(TreeNode*& ptr);

    void SRR(TreeNode*& ptr);

    int getBalance(TreeNode*& current) const;
};  // end of class AVLTree

 