#include "picture.hpp"

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

// void AbstractPuzzle::matrixToTree()
// {
//     Product* puzzle = this->puzzleMatrix[0][0];
//     puzzleTree->setPuzzle(puzzle);
//     puzzleTree->setPosition(std::make_pair<int, int>(0, 0));
//     puzzleTree->setParentLeft(nullptr);
//     puzzleTree->setParentTop(nullptr);
//     BinaryTreeNode* bottomFirst = new BinaryTreeNode();
//     bottomFirst->setPuzzle(this->puzzleMatrix[1][0]);
//     bottomFirst->setPosition(std::make_pair<int, int>(1, 0));
//     puzzleTree->setBottom(bottomFirst);
//     puzzleTree->bottom()->setParentTop(puzzleTree);
//     BinaryTreeNode* rightFirst = new BinaryTreeNode();
//     rightFirst->setPuzzle(this->puzzleMatrix[0][1]);
//     rightFirst->setPosition(std::make_pair<int, int>(0, 1));
//     puzzleTree->setRight(rightFirst);
//     puzzleTree->right()->setParentLeft(puzzleTree);
//     puzzleTree = puzzleTree->right();
//     for(size_t i = 0; i < puzzleMatrix.size(); ++i)
//         for(size_t j = 1; j < puzzleMatrix[0].size(); ++j)
//         {   
//             if (i == 0)
//                 puzzleTree->setParentTop(nullptr);
//             else if (i <= puzzleMatrix.size() - 1)
//             {
//                 BinaryTreeNode* bottom = new BinaryTreeNode();
//                 bottom->setPuzzle(this->puzzleMatrix[i + 1][j]);
//                 bottom->setPosition(std::make_pair<int, int>(i + 1, j));
//                 puzzleTree->setBottom(bottom);
//                 puzzleTree->bottom()->setParentTop(puzzleTree);
//             }
//             if (j == 0)
//                 puzzleTree->setParentLeft(nullptr);
//             else if (j <= puzzleMatrix[0].size() - 1)
//             {
//                 BinaryTreeNode* right = new BinaryTreeNode();
//                 right->setPuzzle(this->puzzleMatrix[i][j + 1]);
//                 right->setPosition(std::make_pair<int, int>(i, j + 1));
//                 if (j < puzzleMatrix[0].size() - 1)
//                 {
//                     puzzleTree->setRight(right);
//                     puzzleTree->right()->setParentLeft(puzzleTree);
//                     puzzleTree = puzzleTree->right();
//                 }
//                 else if (j == puzzleMatrix[0].size() - 1)
//                 {
//                     while(puzzleTree->parentLeft() != nullptr)
//                     {
//                         puzzleTree = puzzleTree->parentLeft();
//                         // std::cout << puzzleTree->position().first << " " << puzzleTree->position().second << " " << puzzleTree->parentLeft() << std::endl;
//                     }
//                     puzzleTree = puzzleTree->bottom();
//                 }
//             }
//             std::cout << puzzleTree->position().first << " " << puzzleTree->position().second << std::endl;
//         }
// }

void AbstractPuzzle::matrixToTree()
{
    Product* puzzle = this->puzzleMatrix[0][0];
    puzzleTree->setPuzzle(puzzle);
    puzzleTree->setPosition(std::make_pair<int, int>(0, 0));
    puzzleTree->setParentLeft(nullptr);
    puzzleTree->setParentTop(nullptr);
    BinaryTreeNode* bottomFirst = new BinaryTreeNode();
    bottomFirst->setPuzzle(this->puzzleMatrix[1][0]);
    bottomFirst->setPosition(std::make_pair<int, int>(1, 0));
    puzzleTree->setBottom(bottomFirst);
    puzzleTree->bottom()->setParentTop(puzzleTree);
    BinaryTreeNode* rightFirst = new BinaryTreeNode();
    rightFirst->setPuzzle(this->puzzleMatrix[0][1]);
    rightFirst->setPosition(std::make_pair<int, int>(0, 1));
    puzzleTree->setRight(rightFirst);
    puzzleTree->right()->setParentLeft(puzzleTree);
    puzzleTree = puzzleTree->right();
    while(puzzleTree->position() != std::make_pair<int, int>(size->height, size->width))
    {
        if (puzzleTree->position().first == 0)
            puzzleTree->setParentTop(nullptr);
        else if (puzzleTree->position().first <= puzzleMatrix.size() - 1)
        {
            BinaryTreeNode* bottom = new BinaryTreeNode();
            bottom->setPuzzle(this->puzzleMatrix[puzzleTree->position().first + 1][puzzleTree->position().second]);
            bottom->setPosition(std::make_pair<int, int>(puzzleTree->position().first + 1, puzzleTree->position().second));
            puzzleTree->setBottom(bottom);
            puzzleTree->bottom()->setParentLeft(puzzleTree);
        }
        if (puzzleTree->position().second == 0)
            puzzleTree->setParentLeft(nullptr);
        else if(puzzleTree->position().second <= puzzleMatrix[0].size() - 1)
        {
            BinaryTreeNode* right = new BinaryTreeNode();
            right->setPuzzle(this->puzzleMatrix[puzzleTree->position().first][puzzleTree->position().second + 1]);
            right->setPosition(std::make_pair<int, int>(puzzleTree->position().first, puzzleTree->position().second + 1));
            if (puzzleTree->position().second < puzzleMatrix[0].size() - 1)
            {
                puzzleTree->setRight(right);
                puzzleTree->right()->setParentLeft(puzzleTree);
                puzzleTree = puzzleTree->right();
            }
            else if (puzzleTree->position().second == puzzleMatrix[0].size() - 1)
            {
                while(puzzleTree->parentLeft() != nullptr)
                {
                    puzzleTree = puzzleTree->parentLeft();
                    // std::cout << puzzleTree->position().first << " " << puzzleTree->position().second << " " << puzzleTree->parentLeft() << std::endl;
                }
                puzzleTree = puzzleTree->bottom();
            }
        }
        std::cout << puzzleTree->position().first << " " << puzzleTree->position().second << " " << puzzleTree->parentLeft() << std::endl;
    }
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
    // sf::Vector2f productSize = puzzleMatrix[0][0]->getSize();
    // float productSize_x = static_cast<float>(productSize.x);
    // float productSize_y = static_cast<float>(productSize.y);
    sf::Vector2f basePuzzleSize(puzzleSize_x / puzzleSize_width, puzzleSize_y / puzzleSize_height);
    // sf::Vector2f basePuzzleSize = this->scaled(sf::Vector2f(puzzleSize_x / puzzleSize_width, puzzleSize_y / puzzleSize_height));
    for (size_t i = 0; i < size->height; ++i)
        for (size_t j = 0; j < size->width; ++j)
        {
            puzzleMatrix[i][j]->setSize(*(new sf::Vector2f(100, 100)));
            sf::Texture* puzzleTexture = new sf::Texture;
            puzzleTexture->loadFromImage(*this->puzzlePicture, sf::IntRect(static_cast<int>(i * basePuzzleSize.x), 
                                                                           static_cast<int>(j * basePuzzleSize.y), 
                                                                           static_cast<int>((i + 1) * basePuzzleSize.x) - static_cast<int>(i * basePuzzleSize.x), 
                                                                           static_cast<int>((j + 1) * basePuzzleSize.y) - static_cast<int>(j * basePuzzleSize.y)));
            puzzleMatrix[i][j]->setBodyTexture(puzzleTexture);
        }
}

void Puzzle::draw(sf::RenderWindow* window)
{
    puzzleMatrix[0][0]->draw(window);
}
