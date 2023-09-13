#include "puzzle.hpp"

PuzzleBody::PuzzleBody(sf::Vector2f& puzzleSize)
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
    puzzleBody_->setFillColor(sf::Color(255, 255, 255, 255));
}

Product::~Product()
{
    if (topSide_) delete topSide_;
    if (bottomSide_) delete bottomSide_;
    if (leftSide_) delete leftSide_;
    if (rightSide_) delete rightSide_;
}

sf::Vector2f Product::getSize()
{
    return this->puzzleBody_->getSize();
}

void Product::setSize(sf::Vector2f& size)
{
    this->puzzleBody_->getSize();
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

void Product::update()
{
    this->topSide_->update();
    this->bottomSide_->update();
    this->leftSide_->update();
    this->rightSide_->update();
}

void Product::draw(sf::RenderWindow* window)
{
    this->topSide_->draw(window);
    this->bottomSide_->draw(window);
    this->leftSide_->draw(window);
    this->rightSide_->draw(window);
    this->puzzleBody_->draw(window);
}

Builder::Builder(sf::Vector2f& puzzleSize) 
    : product(puzzleSize) {}

Product Builder::getProduct()
{
    return this->product;
}

DefaultPuzzleBuilder::DefaultPuzzleBuilder(sf::Vector2f puzzleSize)
    : Builder(puzzleSize) { }

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

void DefaultPuzzleBuilder::update()
{
    this->product.update();
}

void DefaultPuzzleBuilder::draw(sf::RenderWindow* window)
{
    this->product.draw(window);
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

void Director::construct(PuzzleSide* top, PuzzleSide* bottom, PuzzleSide* left, PuzzleSide* right)
{
    builder_->buildTopSide(top);
    builder_->buildBottomSide(bottom);
    builder_->buildLeftSide(left);
    builder_->buildRightSide(right);
}

void Director::update()
{
    builder_->update();
}

void Director::draw(sf::RenderWindow* window)
{
    builder_->draw(window);
}