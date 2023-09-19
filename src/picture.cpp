#include "picture.hpp"

PuzzleSize* PuzzleSize::clone()
{
    return new PuzzleSize(this->width, this->height);
}

AbstractPuzzle::AbstractPuzzle(PuzzleSize* size, std::string pictureFilePath = "")
    : size(size), puzzleTree(nullptr), pictureFilePath(pictureFilePath), puzzlePicture(nullptr), puzzleTexture(nullptr)
{
    puzzleMatrix = std::vector<std::vector<Director*>> (size->height, std::vector<Director*> (size->width));
    puzzlePicture = new sf::Image;
    if(!puzzlePicture->loadFromFile(this->pictureFilePath))
    {
        std::cout << "Unable to load from file: " << this->pictureFilePath << std::endl;
    }
    puzzleTexture = new sf::Texture;
    if(!puzzleTexture->loadFromImage(*puzzlePicture))
    {
        std::cout << "Unable to load from image\n";
    }
}

AbstractPuzzle::~AbstractPuzzle()
{
    this->puzzleMatrix.~vector();
    delete this->puzzlePicture;
    delete this->puzzleTexture;
}

void AbstractPuzzle::setMatrix(std::vector<std::vector<Director*>> matrix)
{
    this->puzzleMatrix = matrix;
}

std::vector<std::vector<Director*>> AbstractPuzzle::getMatrix()
{
    return this->puzzleMatrix;
}

void AbstractPuzzle::setSize(PuzzleSize size)
{
    this->size = size.clone();
}

void AbstractPuzzle::setPictureFilePath(std::string pictureFilePath)
{
    this->pictureFilePath = pictureFilePath;
}

void AbstractPuzzle::setImage(sf::Image* image)
{
    this->puzzlePicture = image;
}

void AbstractPuzzle::setTexture(sf::Texture* texture)
{
    this->puzzleTexture = texture;
}

PuzzleSize* AbstractPuzzle::getSize()
{
    return this->size;
}

std::string AbstractPuzzle::getPictureFilePath()
{
    return this->pictureFilePath;
}

BinaryTreeNode* AbstractPuzzle::getTreeNode()
{
    return this->puzzleTree;
}

sf::Image* AbstractPuzzle::getImage()
{
    return this->puzzlePicture;
}

sf::Texture* AbstractPuzzle::getTexture()
{
    return this->puzzleTexture;
}

Puzzle::Puzzle(PuzzleSize* size, std::string pictureFilePath = "")
    : AbstractPuzzle(size, pictureFilePath) {}

Puzzle::~Puzzle() { }

void Puzzle::parcePicture()
{
    // std::cout << "KK\n";
    sf::Vector2f basePuzzleSize(puzzlePicture->getSize().x / size->width + puzzleMatrix[0][0]->getProduct().getSize().x, 
                                puzzlePicture->getSize().y / size->height + puzzleMatrix[0][0]->getProduct().getSize().y);
    for (size_t i = 0; i < size->height; ++i)
        for (size_t j = 0; j < size->width; ++j)
        {
            sf::Texture* puzzleTexture = new sf::Texture;
            puzzleTexture->loadFromImage(*this->puzzlePicture, sf::IntRect(i * basePuzzleSize.x, j * basePuzzleSize.y, 
                                                                          (i + 1) * basePuzzleSize.x, (j + 1) * basePuzzleSize.y));
            DefaultPuzzleBuilder* builder = new DefaultPuzzleBuilder(sf::Vector2f(puzzlePicture->getSize().x, 
                                                                                  puzzlePicture->getSize().y));
            puzzleMatrix[i][j] = new Director(builder);
            puzzleMatrix[i][j]->setBodyTexture(puzzleTexture);
        }
}

void Puzzle::draw(sf::RenderWindow* window)
{
    puzzleMatrix[0][0]->draw(window);
}
