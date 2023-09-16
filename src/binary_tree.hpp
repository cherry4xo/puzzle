#ifndef BINARY_TREE_HEADER
#define BINARY_TREE_HEADER

#include "puzzle.hpp"
#include <deque>
#include <vector>
#include <climits>

class BinaryTreeNode
{
public:
    BinaryTreeNode();
    ~BinaryTreeNode();

    BinaryTreeNode* right(); 
    BinaryTreeNode* bottom(); 
    BinaryTreeNode* parent(); 

    void setRight(BinaryTreeNode* right); 
    void setBottom(BinaryTreeNode* bottom); 
    void setParent(BinaryTreeNode* parent);

    Director* puzzle();
    void setPuzzle(Director* puzzle);

private:
    BinaryTreeNode* right_;
    BinaryTreeNode* bottom_;
    BinaryTreeNode* parent_;
    Director* puzzle_;
};



#endif