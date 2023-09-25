#pragma once

#ifndef PATTERN_HEADER
#define PATTERN_HEADER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sys/types.h>
#include <tuple>
#include <math.h>
#include <cmath>
#include <vector>   

enum class Rotation {top, bottom, left, right};

class ShapeStrategy : public sf::Shape
{
public:
    explicit ShapeStrategy(const u_int16_t point_count, const Rotation srot);
    virtual ~ShapeStrategy();
    size_t getPointCount() const override;
    sf::Vector2f getPoint(size_t index) const override;
    virtual void set_point_count(const u_int16_t point_count);
    virtual void set_size(const sf::Vector2f&) = 0;
    virtual const sf::Vector2f& get_size() = 0;
    virtual inline void getPoints() = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow*) = 0;
    virtual ShapeStrategy* clone() = 0;
protected:
    size_t point_count_;
    std::vector<sf::Vector2f> points_;
    const Rotation srot_;
};

class EllipceStrategy : public ShapeStrategy
{
public:
    EllipceStrategy(const sf::Vector2f& radius, 
                    const sf::Vector2f& position,
                    const Rotation srot,
                    u_int16_t point_count);
    virtual ~EllipceStrategy();
    void set_size(const sf::Vector2f& radius) override;
    inline void getPoints() override;
    const sf::Vector2f& get_size() override;
    void update() override;
    void draw(sf::RenderWindow* window) override;
    EllipceStrategy* clone() override;
protected:
    sf::Vector2f radius_;
    sf::VertexArray* shape_ = nullptr;
};

class PuzzleSide
{
public:
    PuzzleSide(ShapeStrategy* s);
    virtual ~PuzzleSide();
    PuzzleSide* clone();
    void set_shape(ShapeStrategy* s);
    void set_point_count(u_int16_t point_count);
    size_t getPointCount();
    void set_size(const sf::Vector2f& radius);
    const sf::Vector2f& get_size();
    void update();
    void draw(sf::RenderWindow* window);
    void setPosition(sf::Vector2f position);
protected:
    ShapeStrategy* shapeStrategy_ = nullptr;
};

#endif