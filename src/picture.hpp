#ifndef PICTURE_HEADER
#define PICTURE_HEADER

#include <iostream>
#include <string>
#include "pattern.hpp"
#include "puzzle.hpp"


class AbstractPuzzle
{
    std::string pictureFilePath;
    sf::Image puzzlePicture;
    sf::Texture puzzleTexture;
    
};

#endif