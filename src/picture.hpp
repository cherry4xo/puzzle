#pragma once

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
    virtual void setMatrix(std::vector<std::vector<Director*>> matrix);
    virtual std::vector<std::vector<Director*>> getMatrix(); 
    virtual void parcePicture() = 0;     

    PuzzleSize size;
    std::vector<std::vector<Director*>> puzzleMatrix;
    BinaryTreeNode* puzzleTree;
    std::string pictureFilePath;
    sf::Image* puzzlePicture;
    sf::Texture* puzzleTexture;
};

class Puzzle : public AbstractPuzzle
{
public:
    Puzzle(PuzzleSize size);
    virtual ~Puzzle();
    void parcePicture() override;
};

#endif