#pragma once

#ifndef PICTURE_HEADER
#define PICTURE_HEADER

#include <iostream>
#include <string>
#include <cstdlib>
#include "pattern.hpp"
#include "puzzle.hpp"
#include "binary_tree.hpp"
#include "config.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct PuzzleSize
{
    PuzzleSize(const u_int16_t width, const u_int16_t height)
        : width(width), height(height) {}
    const u_int16_t width, height;
    PuzzleSize* clone();
};

class AbstractPuzzle
{
public:
    AbstractPuzzle(PuzzleSize* size, std::string pictureFilePath);
    virtual ~AbstractPuzzle();  
    virtual void setMatrix(std::vector<std::vector<Product*>> matrix);
    virtual std::vector<std::vector<Product*>> getMatrix(); 
    virtual void parcePicture() = 0;

    virtual void initMatrix(PuzzleSide* top, PuzzleSide* bottom, PuzzleSide* left, PuzzleSide* right);
    virtual void initMatrixWithRandomSides();
    virtual inline sf::Vector2f scaled(sf::Vector2f size);
    virtual sf::Vector2f getRandomVectorHorizontalSide();
    virtual sf::Vector2f getRandomVectorVerticalSide();

    virtual void setSize(PuzzleSize size);
    virtual void setPictureFilePath(std::string pictureFilePath);
    virtual void setImage(sf::Image* image);
    virtual void setTexture(sf::Texture* texture);

    virtual PuzzleSize* getSize();
    virtual std::string getPictureFilePath();
    virtual BinaryTreeNode* getTreeNode();
    virtual sf::Image* getImage();
    virtual sf::Texture* getTexture();

    virtual void matrixToTree();
    void getDefaultBottomNode();
    void getDefaultRightNode();

    sf::RenderStates getRenderState();

    PuzzleSize* size;
    std::vector<std::vector<Product*>> puzzleMatrix;
    Director puzzleProductDirector;
    BinaryTreeNode* puzzleTree;
    std::string pictureFilePath;
    sf::Image* puzzlePicture;
    sf::Texture* puzzleTexture;
    sf::RenderStates renderState;
};

class Puzzle : public AbstractPuzzle
{
public:
    Puzzle(PuzzleSize* size, std::string pictureFilePath);
    ~Puzzle();
    void parcePicture() override;
    void draw(sf::RenderWindow* window);
};

#endif