#include "picture.hpp"

AbstractPuzzle::AbstractPuzzle(PuzzleSize size)
    : size(size), puzzleTree(new BinaryTreeNode), puzzlePicture(new sf::Image), puzzleTexture(new sf::Texture) 
{
    puzzleMatrix = std::vector<std::vector<PuzzleSide>> (size.height, std::vector<PuzzleSide> (size.width));
    puzzlePicture->loadFromFile(this->pictureFilePath);
    puzzleTexture->loadFromImage(*puzzlePicture);
}

AbstractPuzzle::~AbstractPuzzle()
{
    this->puzzleMatrix.~vector();
    delete this->puzzlePicture;
    delete this->puzzleTexture;
}

void AbstractPuzzle::setMatrix(std::vector<std::vector<PuzzleSide>> matrix)
{
    this->puzzleMatrix = matrix;
}

std::vector<std::vector<PuzzleSide>> AbstractPuzzle::getMatrix()
{
    return this->puzzleMatrix;
}

Puzzle::Puzzle(PuzzleSize size)
    : AbstractPuzzle(size) {}

Puzzle::~Puzzle() { }

void Puzzle::parcePicture()
{
    sf::Vector2f basePuzzleSize(puzzlePicture->getSize().x / size.width + puzzleMatrix[0][0].get_size().x, 
                                puzzlePicture->getSize().y / size.height + puzzleMatrix[0][0].get_size().y);
    for (size_t i = 0; i < size.height; ++i)
        for (size_t j = 0; j < size.width; ++i)
        {
            sf::Texture* puzzleTexture = new sf::Texture;
            puzzleTexture->loadFromImage(*this->puzzlePicture, sf::IntRect(i * basePuzzleSize.x, j * basePuzzleSize.y, 
                                                                          (i + 1) * basePuzzleSize.x, (j + 1) * basePuzzleSize.y));
        }
}
