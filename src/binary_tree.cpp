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
BinaryTreeNode* BinaryTreeNode::parentLeft()
{
    return this->parentLeft_;
}
BinaryTreeNode* BinaryTreeNode::parentTop()
{
    return this->parentTop_;
}

void BinaryTreeNode::setRight(BinaryTreeNode* right)
{
    this->right_ = right;
}
void BinaryTreeNode::setBottom(BinaryTreeNode* bottom)
{
    this->bottom_ = bottom;
}
void BinaryTreeNode::setParentLeft(BinaryTreeNode* parentLeft)
{
    this->parentLeft_ = parentLeft;
}
void BinaryTreeNode::setParentTop(BinaryTreeNode* parentTop)
{
    this->parentTop_ = parentTop;
}

Product* BinaryTreeNode::puzzle()
{
    return this->puzzle_;
}
void BinaryTreeNode::setPuzzle(Product* puzzle)
{
    this->puzzle_ = puzzle;
}

std::pair<int, int> BinaryTreeNode::position()
{
    return this->position_;
}
void BinaryTreeNode::setPosition(std::pair<int, int> pos)
{
    this->position_ = pos;
}


IBinaryTree::IBinaryTree()
{ }

IBinaryTree::~IBinaryTree()
{ }

inline bool IBinaryTree::checkIfNeighbours(BinaryTreeNode* first, BinaryTreeNode* second)
{
    return (first->bottom() == second || first->right() == second || first->parentLeft() == second || first->parentTop() == second);
}



