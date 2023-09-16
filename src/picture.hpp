#ifndef PICTURE_HEADER
#define PICTURE_HEADER

#include <iostream>
#include <string>
#include "pattern.hpp"
#include "puzzle.hpp"
#include "binary_tree.hpp"

struct PuzzleSize
{
    PuzzleSize(const u_int16_t width, const u_int16_t height)
        : width(width), height(height) {}
    const u_int16_t width, height;
};

class AbstractPuzzle
{
public:
    AbstractPuzzle(PuzzleSize size);
    virtual ~AbstractPuzzle();  
    virtual void setMatrix(std::vector<std::vector<PuzzleSide>> matrix);
    virtual std::vector<std::vector<PuzzleSide>> getMatrix();      

    PuzzleSize size;
    std::vector<std::vector<PuzzleSide>> PuzzleMatrix;
    BinaryTreeNode* puzzleTree;
    std::string pictureFilePath;
    sf::Image* puzzlePicture;
    sf::Texture* puzzleTexture;
};





#endif