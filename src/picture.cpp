#include "picture.hpp"
#include <unistd.h>

PuzzleSize* PuzzleSize::clone()
{
    return new PuzzleSize(this->width, this->height);
}

AbstractPuzzle::AbstractPuzzle(PuzzleSize* size, std::string pictureFilePath = "")
    : size(size), 
      puzzleProductDirector(new DefaultPuzzleBuilder(sf::Vector2f(size->width, size->height))), 
      puzzleTree(nullptr), 
      pictureFilePath(pictureFilePath), 
      puzzlePicture(nullptr), 
      puzzleTexture(nullptr)
{
    // DefaultPuzzleBuilder* puzzleBuilder = new DefaultPuzzleBuilder(sf::Vector2f(size->width, size->height));
    // Director* puzzleProductDirector = new Director(puzzleBuilder);
    srand((unsigned) time(NULL));
    puzzleTree = new BinaryTreeNode();
    puzzleMatrix = std::vector<std::vector<Product*>> (size->height, std::vector<Product*> (size->width));
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

void AbstractPuzzle::initMatrix(PuzzleSide* top, PuzzleSide* bottom, PuzzleSide* left, PuzzleSide* right)
{
    puzzleProductDirector.construct(top, bottom, left, right);
    for(size_t i = 0; i < size->height; ++i)
        for(size_t j = 0; j < size->width; ++j)
        {
            Product* puzzleProduct = puzzleProductDirector.getClonedProduct();
            this->puzzleMatrix[i][j] = puzzleProduct;
        }
}

sf::Vector2f AbstractPuzzle::getRandomVectorHorizontalSide()
{
    int minWidth = SCREEN_SIZE::WIDTH / size->width / 8;
    int minHeight = SCREEN_SIZE::HEIGHT / size->height / 8;
    int rangeHeight = rand() % (SCREEN_SIZE::HEIGHT / size->height / 4);
    sf::Vector2f vect(static_cast<int>(minWidth),
                      static_cast<int>(minHeight + rangeHeight));
    return vect;
}

sf::Vector2f AbstractPuzzle::getRandomVectorVerticalSide()
{
    int minWidth = SCREEN_SIZE::WIDTH / size->width / 8;
    int minHeight = SCREEN_SIZE::HEIGHT / size->height / 8;
    int rangeWidth = rand() % (SCREEN_SIZE::WIDTH / size->width / 4);
    sf::Vector2f vect(static_cast<int>(minWidth + rangeWidth),
                      static_cast<int>(minHeight));
    return vect;
}

void AbstractPuzzle::initMatrixWithRandomSides()
{
    for(size_t i = 0; i < size->height; ++i)
        for(size_t j = 0; j < size->width; ++j)
        {
            PuzzleSide* top = nullptr, *bottom = nullptr, *left = nullptr, *right = nullptr;
            if (i == 0)
                top = new PuzzleSide(new EllipceStrategy(sf::Vector2f(0, 0), sf::Vector2f(0, 0), Rotation::top, 30));
            else
                top = new PuzzleSide(new EllipceStrategy(getRandomVectorHorizontalSide(), sf::Vector2f(0, 0), Rotation::top, 30));
            if (i == size->height - 1)
                bottom = new PuzzleSide(new EllipceStrategy(sf::Vector2f(0, 0), sf::Vector2f(0, 0), Rotation::bottom, 30));
            else
                bottom = new PuzzleSide(new EllipceStrategy(getRandomVectorHorizontalSide(), sf::Vector2f(0, 0), Rotation::bottom, 30));
            if (j == 0)
                left = new PuzzleSide(new EllipceStrategy(sf::Vector2f(0, 0), sf::Vector2f(0, 0), Rotation::left, 30));
            else
                left = new PuzzleSide(new EllipceStrategy(getRandomVectorVerticalSide(), sf::Vector2f(0, 0), Rotation::left, 30));
            if (j == size->width - 1)
                right = new PuzzleSide(new EllipceStrategy(sf::Vector2f(0, 0), sf::Vector2f(0, 0), Rotation::right, 30));
            else
                right = new PuzzleSide(new EllipceStrategy(getRandomVectorVerticalSide(), sf::Vector2f(0, 0), Rotation::right, 30));
            puzzleProductDirector.construct(top, bottom, left, right);
            Product* puzzleProduct = puzzleProductDirector.getClonedProduct();
            this->puzzleMatrix[i][j] = puzzleProduct;
        }
}

inline sf::Vector2f AbstractPuzzle::scaled(sf::Vector2f size)
{
    float scale_x = (SCREEN_WIDTH / static_cast<float>(this->puzzlePicture->getSize().x));
    float scale_y = (SCREEN_HEIGHT / static_cast<float>(this->puzzlePicture->getSize().y));
    return sf::Vector2f(static_cast<int>(size.x * scale_x), static_cast<int>(size.y * scale_y));
}

void AbstractPuzzle::setMatrix(std::vector<std::vector<Product*>> matrix)
{
    this->puzzleMatrix = matrix;
}

std::vector<std::vector<Product*>> AbstractPuzzle::getMatrix()
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

void AbstractPuzzle::getDefaultBottomNode()
{
    BinaryTreeNode* bottom = new BinaryTreeNode();
    bottom->setPuzzle(this->puzzleMatrix[puzzleTree->position().first + 1][puzzleTree->position().second]->clone());
    bottom->setPosition(std::make_pair<int, int>(puzzleTree->position().first + 1, puzzleTree->position().second));
    puzzleTree->setBottom(bottom);
    puzzleTree->bottom()->setParentTop(puzzleTree);
}

void AbstractPuzzle::getDefaultRightNode()
{
    BinaryTreeNode* right = new BinaryTreeNode();
    right->setPuzzle(this->puzzleMatrix[puzzleTree->position().first][puzzleTree->position().second + 1]->clone());
    right->setPosition(std::make_pair<int, int>(puzzleTree->position().first, puzzleTree->position().second + 1));
    puzzleTree->setRight(right);
    puzzleTree->right()->setParentLeft(puzzleTree);
}

void AbstractPuzzle::matrixToTree()
{
    Product* puzzle = this->puzzleMatrix[0][0]->clone();
    puzzleTree->setPuzzle(puzzle);
    puzzleTree->setPosition(std::make_pair<int, int>(0, 0));
    puzzleTree->setParentLeft(nullptr);
    puzzleTree->setParentTop(nullptr);
    this->getDefaultBottomNode();
    this->getDefaultRightNode();
    BinaryTreeNode* firstNode = puzzleTree;
    puzzleTree = puzzleTree->right();
    while(puzzleTree->position() != std::make_pair<int, int>(size->height - 1, size->width - 1))
    {
        if (puzzleTree->position().first == puzzleMatrix.size() - 1)
            puzzleTree->setBottom(nullptr);
        else
        {   
            this->getDefaultBottomNode();
            if (puzzleTree->position().first == 0)
                puzzleTree->setParentTop(nullptr);
        }

        if (puzzleTree->position().second == puzzleMatrix[0].size() - 1)
        {
            puzzleTree->setRight(nullptr);
            while (puzzleTree->parentLeft() != nullptr)
            {
                puzzleTree = puzzleTree->parentLeft();
            }
            puzzleTree = puzzleTree->bottom();
        }
        else
        {
            this->getDefaultRightNode();
            if (puzzleTree->position().second == 0)
                puzzleTree->setParentLeft(nullptr);
            puzzleTree = puzzleTree->right();
        }
    }
    puzzleTree = firstNode;
}

Puzzle::Puzzle(PuzzleSize* size, std::string pictureFilePath = "")
    : AbstractPuzzle(size, pictureFilePath) {}

Puzzle::~Puzzle() { }

void Puzzle::parcePicture()
{
    // TODO make puzzle texture scale (completed)
    float pictureSize_x = static_cast<float>(puzzlePicture->getSize().x);
    float pictureSize_y = static_cast<float>(puzzlePicture->getSize().y);
    float puzzleSize_width = static_cast<float>(size->width);
    float puzzleSize_height = static_cast<float>(size->height);
    float scale_x = pictureSize_x / puzzleSize_width;
    float scale_y = pictureSize_y / puzzleSize_height;
    sf::Vector2f puzzleSizeScaled(static_cast<float>(SCREEN_SIZE::WIDTH) / puzzleSize_width, 
                                  static_cast<float>(SCREEN_SIZE::HEIGHT) / puzzleSize_height);
    sf::Vector2f basePuzzleSize(scale_x, scale_y);
    for (size_t i = 0; i < size->height; ++i)
        for (size_t j = 0; j < size->width; ++j)
        {
            puzzleMatrix[i][j]->setSize(puzzleSizeScaled);
            sf::Texture* texture = new sf::Texture;
            texture->loadFromImage(*this->puzzlePicture, sf::IntRect(static_cast<int>(i * basePuzzleSize.x), 
                                                                    static_cast<int>(j * basePuzzleSize.y), 
                                                                    static_cast<int>((i + 1) * basePuzzleSize.x) - static_cast<int>(i * basePuzzleSize.x), 
                                                                    static_cast<int>((j + 1) * basePuzzleSize.y) - static_cast<int>(j * basePuzzleSize.y)));
            puzzleMatrix[i][j]->setBodyTexture(texture);
            puzzleMatrix[i][j]->update();
            std::vector<sf::Vector2f> pointsTop = puzzleMatrix[i][j]->getTopSide()->getShape()->getPointsArray();
            for (size_t k = 0; k < pointsTop.size(); ++k)
            {
                puzzleMatrix[i][j]->getTopSide()->getShape()->getShapeArray()[0][k].texCoords = sf::Vector2f(i * basePuzzleSize.x + (this->puzzleMatrix[i][j]->getSize().x - puzzleMatrix[i][j]->getTopSide()->get_size().x) / 2 + pointsTop[k].x,
                                                                                                            i * basePuzzleSize.x - puzzleMatrix[i][j]->getTopSide()->get_size().x + pointsTop[k].x);
            }
        }
}

void Puzzle::draw(sf::RenderWindow* window)
{
    puzzleMatrix[0][0]->draw(window);
}
