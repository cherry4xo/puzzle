#include "algorithm.hpp"

Algorithm::Algorithm(u_int16_t puzzleCount_x, u_int16_t puzzleCount_y, std::string pictureFilePath)
    : puzzle_(nullptr)
{
    puzzle_ = new Puzzle(new PuzzleSize(puzzleCount_x, puzzleCount_y), pictureFilePath);
    puzzle_->initMatrixWithRandomSides();
    puzzle_->parcePicture();
    puzzle_->matrixToTree();
}

Algorithm::~Algorithm()
{
    puzzle_->~Puzzle();
}

void Algorithm::drawAllPuzzle(sf::RenderWindow* window)
{
    for (size_t i = 0; i < puzzle_->getSize()->height; ++i)
        for (size_t j = 0; j < puzzle_->getSize()->width; ++j)
        {
            puzzle_->getMatrix()[i][j]->draw(window);
        }
}

void Algorithm::setDefaultPositionAllPuzzle()
{
    for (size_t i = 0; i < puzzle_->getSize()->height; ++i)
        for (size_t j = 0; j < puzzle_->getSize()->width; ++j)
        {
            puzzle_->getMatrix()[i][j]->setBodyPosition(sf::Vector2f(i * puzzle_->getMatrix()[0][0]->getSize().x, j * puzzle_->getMatrix()[0][0]->getSize().y));
            puzzle_->getMatrix()[i][j]->update();
        }
}
