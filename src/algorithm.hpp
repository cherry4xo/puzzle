#pragma once

#ifndef ALGORITHM_HEADER
#define ALGORITHM_HEADER

#include "picture.hpp"


class Algorithm
{
public:
    Algorithm(u_int16_t puzzleCount_x, u_int16_t puzzleCount_y, std::string pictureFilePath);
    ~Algorithm();
    void drawAllPuzzle(sf::RenderWindow* window);
    void setDefaultPositionAllPuzzle();
private:
    Puzzle* puzzle_;
};


#endif