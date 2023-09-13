#pragma once

#ifndef PUZZLE_HEADER
#define PUZZLE_HEADER

#include <SFML/Graphics.hpp>
#include "pattern.hpp"

class PuzzleBody : public sf::RectangleShape
{
public:
    PuzzleBody(sf::Vector2f& puzzleSize);
    ~PuzzleBody();

    void draw(sf::RenderWindow* window);
};

class Product
{
public:
    Product(sf::Vector2f& puzzleSize);
    ~Product();

    sf::Vector2f getSize();
    void setSize(sf::Vector2f& size);

    void topSide(PuzzleSide* side);
    void bottomSide(PuzzleSide* side);
    void leftSide(PuzzleSide* side);
    void rightSide(PuzzleSide* side);

    void setBodyPosition(sf::Vector2f position);
    void update();
    void draw(sf::RenderWindow* window);
    
private:
    PuzzleSide* topSide_ = nullptr, 
                *bottomSide_ = nullptr, 
                *leftSide_ = nullptr, 
                *rightSide_ = nullptr;
    PuzzleBody* puzzleBody_ = nullptr;
};

class Builder
{
public:
    Builder(sf::Vector2f& puzzleSize);
    virtual ~Builder() = default;
    virtual Product getProduct();

    virtual void buildTopSide(PuzzleSide*) = 0;
    virtual void buildBottomSide(PuzzleSide*) = 0;
    virtual void buildLeftSide(PuzzleSide*) = 0;
    virtual void buildRightSide(PuzzleSide*) = 0;

    virtual void setPosition(sf::Vector2f position) = 0;
    virtual sf::Vector2f getBodySize() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow*) = 0;

protected:
    Product product;
};

class DefaultPuzzleBuilder : public Builder
{
public:
    DefaultPuzzleBuilder(sf::Vector2f puzzleSize);
    ~DefaultPuzzleBuilder() = default;
    Product getProduct() override;

    void buildTopSide(PuzzleSide* side) override;
    void buildBottomSide(PuzzleSide* side) override;
    void buildLeftSide(PuzzleSide* side) override;
    void buildRightSide(PuzzleSide* side) override;

    void setPosition(sf::Vector2f position) override;
    sf::Vector2f getBodySize() override;
    void update() override;
    void draw(sf::RenderWindow* window) override; 
};

class Director
{
public:
    Director(Builder* builder);
    ~Director();

    void setBuilder(Builder* builder);

    Product getProduct();

    void construct(PuzzleSide* top, PuzzleSide* bottom, PuzzleSide* left, PuzzleSide* right);

    sf::Vector2f getBodySize();
    void setPosition(sf::Vector2f position); 
    void update();
    void draw(sf::RenderWindow* window);

private:
    Builder* builder_ = nullptr;
};

#endif