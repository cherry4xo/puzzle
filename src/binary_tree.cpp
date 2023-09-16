#include "binary_tree.hpp"

BinaryTreeNode::BinaryTreeNode() {}
BinaryTreeNode::~BinaryTreeNode() 
{
    delete this->puzzle_;
}

BinaryTreeNode* BinaryTreeNode::right()
{
    return this->right_;
}
BinaryTreeNode* BinaryTreeNode::bottom()
{
    return this->bottom_;
}
BinaryTreeNode* BinaryTreeNode::parent()
{
    return this->parent_;
}

void BinaryTreeNode::setRight(BinaryTreeNode* right)
{
    this->right_ = right;
}
void BinaryTreeNode::setBottom(BinaryTreeNode* bottom)
{
    this->bottom_ = bottom;
}
void BinaryTreeNode::setParent(BinaryTreeNode* parent)
{
    this->parent_ = parent;
}

Director* BinaryTreeNode::puzzle()
{
    return this->puzzle_;
}
void BinaryTreeNode::setPuzzle(Director* puzzle)
{
    this->puzzle_ = puzzle;
}

