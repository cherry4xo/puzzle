#pragma once

#ifndef PUZZLE_HEADER
#define PUZZLE_HEADER

#include <SFML/Graphics.hpp>
#include "pattern.hpp"

class Product
{
public:
    void topSide(ShapeStrategy* shape);
    void bottomSide(ShapeStrategy* shape);
    void leftSide(ShapeStrategy* shape);
    void rightSide(ShapeStrategy* shape);
    
private:
    PuzzleSide* topSide, bottomSide, leftSide, rightSide;
    sf::Vector2f puzzleSize;
};

#endif