#pragma once

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
    BinaryTreeNode* parentLeft(); 
    BinaryTreeNode* parentTop();

    void setRight(BinaryTreeNode* right); 
    void setBottom(BinaryTreeNode* bottom); 
    void setParentLeft(BinaryTreeNode* parentLeft);
    void setParentTop(BinaryTreeNode* parentTop);

    Product* puzzle();
    void setPuzzle(Product* puzzle);

    std::pair<int, int> position();
    void setPosition(std::pair<int, int> pos);

private:
    BinaryTreeNode* right_;
    BinaryTreeNode* bottom_;
    BinaryTreeNode* parentLeft_;
    BinaryTreeNode* parentTop_;
    Product* puzzle_;
    std::pair<int, int> position_;
};


class IBinaryTree
{
public:
    IBinaryTree();
    ~IBinaryTree();

    bool checkIfNeighbours(BinaryTreeNode* first, BinaryTreeNode* second);
private:
    BinaryTreeNode* treeNode;
};


#endif