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
    delete this->puzzlePicture;
    delete this->puzzleTexture;
}

void AbstractPuzzle::initMatrix(DefaultPuzzleBuilder* builder, PuzzleSide* top, PuzzleSide* bottom, PuzzleSide* left, PuzzleSide* right)
{
    for(size_t i = 0; i < size->height; ++i)
        for(size_t j = 0; j < size->width; ++j)
        {
            this->puzzleMatrix[i][j] = new Director(builder);
            this->puzzleMatrix[i][j]->construct(top, bottom, left, right);
        }
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
    float puzzleSize_x = static_cast<float>(puzzlePicture->getSize().x);
    float puzzleSize_y = static_cast<float>(puzzlePicture->getSize().y);
    float puzzleSize_width = static_cast<float>(size->width);
    float puzzleSize_height = static_cast<float>(size->height);
    sf::Vector2f productSize = puzzleMatrix[0][0]->getProduct().getSize();
    float productSize_x = static_cast<float>(productSize.x);
    float productSize_y = static_cast<float>(productSize.y);
    // TODO make smth with puzzle size
    // sf::Vector2f basePuzzleSize(puzzleSize_x / puzzleSize_width + productSize_x, puzzleSize_y / puzzleSize_height + productSize_y);
    sf::Vector2f basePuzzleSize(puzzleSize_x / puzzleSize_width, puzzleSize_y / puzzleSize_height);
    std::cout << basePuzzleSize.x << " " << basePuzzleSize.y << std::endl;
    for (size_t i = 0; i < size->height; ++i)
        for (size_t j = 0; j < size->width; ++j)
        {
            sf::Texture* puzzleTexture = new sf::Texture;
            puzzleTexture->loadFromImage(*this->puzzlePicture, sf::IntRect(static_cast<int>(i * basePuzzleSize.x), 
                                                                           static_cast<int>(j * basePuzzleSize.y), 
                                                                           static_cast<int>((i + 1) * basePuzzleSize.x) - static_cast<int>(i * basePuzzleSize.x), 
                                                                           static_cast<int>((j + 1) * basePuzzleSize.y) - static_cast<int>(j * basePuzzleSize.y)));
            std::cout << puzzleTexture->getSize().x << " " << puzzleTexture->getSize().y << std::endl;
            // std::cout << static_cast<int>(i * basePuzzleSize.x) << " " << static_cast<int>(j * basePuzzleSize.y) 
                    //   << " " << static_cast<int>((i + 1) * basePuzzleSize.x) << " " << static_cast<int>((j + 1) * basePuzzleSize.y) << std::endl;
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
