#include "puzzle.hpp"

PuzzleBody::PuzzleBody(sf::Vector2f& puzzleSize)
    : RectangleShape(puzzleSize)
{
    this->setSize(puzzleSize);
    this->setFillColor(sf::Color(255, 255, 255, 255));
}

PuzzleBody::~PuzzleBody() {}

void PuzzleBody::draw(sf::RenderWindow* window)
{
    window->draw(*this);
}

Product::Product(sf::Vector2f& puzzleSize)
    :puzzleBody_(new PuzzleBody(puzzleSize))
{
    // this->topSide_ = new PuzzleSide();
    // this->bottomSide_ = new PuzzleSide();
    // this->leftSide_ = new PuzzleSide();
    // this->rightSide_ = new PuzzleSide();
    puzzleBody_->setFillColor(sf::Color(255, 255, 255, 255));
}

Product::~Product()
{
    if (topSide_) delete topSide_;
    if (bottomSide_) delete bottomSide_;
    if (leftSide_) delete leftSide_;
    if (rightSide_) delete rightSide_;
}

Product* Product::clone()
{
    sf::Vector2f* size = new sf::Vector2f(this->getSize().x, this->getSize().y);
    Product* newProduct = new Product(*size);
    newProduct->topSide(this->topSide_->clone());
    newProduct->bottomSide(this->bottomSide_->clone());
    newProduct->leftSide(this->leftSide_->clone());
    newProduct->rightSide(this->rightSide_->clone());
    newProduct->puzzleBody_ = new PuzzleBody(*size);
    newProduct->puzzleTexture = new sf::Texture;
    newProduct->puzzleTexture = this->puzzleTexture;
    newProduct->puzzleBody_->setPosition(this->puzzleBody_->getPosition());
    // newProduct->puzzleBody_->setTexture(newProduct->puzzleTexture);
    return newProduct;
}   

sf::Vector2f Product::getSize()
{
    return this->puzzleBody_->getSize();
}

void Product::setSize(sf::Vector2f& size)
{
    this->puzzleBody_->setSize(size);
}

void Product::topSide(PuzzleSide* side)
{
    this->topSide_ = side;
}
void Product::bottomSide(PuzzleSide* side)
{
    this->bottomSide_ = side;
}
void Product::leftSide(PuzzleSide* side)
{
    this->leftSide_ = side;
}
void Product::rightSide(PuzzleSide* side)
{
    this->rightSide_ = side;
}

void Product::setBodyPosition(sf::Vector2f position)
{
    this->puzzleBody_->setPosition(position);
}

void Product::update()
{
    topSide_->setPosition(sf::Vector2f(puzzleBody_->getPosition().x + puzzleBody_->getSize().x / 2, 
                                       puzzleBody_->getPosition().y));
    bottomSide_->setPosition(sf::Vector2f(puzzleBody_->getPosition().x + puzzleBody_->getSize().x / 2, 
                                         puzzleBody_->getPosition().y + puzzleBody_->getSize().y));
    leftSide_->setPosition(sf::Vector2f(puzzleBody_->getPosition().x, 
                                        puzzleBody_->getPosition().y + puzzleBody_->getSize().y / 2));
    rightSide_->setPosition(sf::Vector2f(puzzleBody_->getPosition().x + puzzleBody_->getSize().x, 
                                       puzzleBody_->getPosition().y + puzzleBody_->getSize().y / 2));
    this->topSide_->update();
    this->bottomSide_->update();
    this->leftSide_->update();
    this->rightSide_->update();
}

PuzzleSide* Product::getTopSide()
{
    return this->topSide_;
}

PuzzleSide* Product::getBottomSide()
{
    return this->bottomSide_;
}

PuzzleSide* Product::getLeftSide()
{
    return this->leftSide_;
}

PuzzleSide* Product::getRightSide()
{
    return this->rightSide_;
}

void Product::draw(sf::RenderWindow* window)
{
    this->topSide_->draw(window);
    this->bottomSide_->draw(window);
    this->leftSide_->draw(window);
    this->rightSide_->draw(window);
    this->puzzleBody_->draw(window);
}

void Product::setBodyTexture(sf::Texture* texture)
{
    puzzleBody_->setTexture(texture);
    this->puzzleTexture = texture;
}

void Product::updateTexture(const sf::Texture* texture)
{
    this->puzzleTexture->update(*texture);
}

sf::Texture* Product::getBodyTexture()
{
    return this->puzzleTexture;
}

Builder::Builder(sf::Vector2f& puzzleSize) 
    : product(puzzleSize) {}

Product Builder::getProduct()
{
    return product;
}

Product* Builder::getClonedProduct()
{
    return product.clone();
}

DefaultPuzzleBuilder::DefaultPuzzleBuilder(sf::Vector2f puzzleSize)
    : Builder(puzzleSize) { }

Product DefaultPuzzleBuilder::getProduct()
{
    return product;
}

void DefaultPuzzleBuilder::buildTopSide(PuzzleSide* side) 
{
    this->product.topSide(side);
}
void DefaultPuzzleBuilder::buildBottomSide(PuzzleSide* side)
{
    this->product.bottomSide(side);
}
void DefaultPuzzleBuilder::buildLeftSide(PuzzleSide* side)
{
    this->product.leftSide(side);
}
void DefaultPuzzleBuilder::buildRightSide(PuzzleSide* side)
{
    this->product.rightSide(side);
}

void DefaultPuzzleBuilder::setPosition(sf::Vector2f position)
{
    this->product.setBodyPosition(position);
}

sf::Vector2f DefaultPuzzleBuilder::getBodySize()
{
    return this->product.getSize();
}

void DefaultPuzzleBuilder::update()
{
    this->product.update();
}

void DefaultPuzzleBuilder::draw(sf::RenderWindow* window)
{
    this->product.draw(window);
}

void DefaultPuzzleBuilder::setBodyTexture(sf::Texture* texture)
{
    this->product.setBodyTexture(texture);
}

Director::Director(Builder* builder)
    : builder_(builder) { }
Director::~Director()
{
    if(builder_) delete builder_;
}

void Director::setBuilder(Builder* builder)
{
    if(builder_) delete builder_;
    builder_ = builder;
}

Product Director::getProduct()
{
    return builder_->getProduct();
}

Product* Director::getClonedProduct()
{
    return builder_->getClonedProduct();
}

void Director::construct(PuzzleSide* top, PuzzleSide* bottom, PuzzleSide* left, PuzzleSide* right)
{
    builder_->buildTopSide(top);
    builder_->buildBottomSide(bottom);
    builder_->buildLeftSide(left);
    builder_->buildRightSide(right);
}

void Director::setPosition(sf::Vector2f position)
{
    this->builder_->setPosition(position);
}

sf::Vector2f Director::getBodySize()
{
    return builder_->getBodySize();
}

void Director::update()
{
    builder_->update();
}

void Director::draw(sf::RenderWindow* window)
{
    builder_->draw(window);
}

void Director::setBodyTexture(sf::Texture* texture)
{
    builder_->getProduct().setBodyTexture(texture);
}