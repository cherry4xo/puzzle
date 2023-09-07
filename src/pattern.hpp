#pragma once

#ifndef PATTERN_HEADER
#define PATTERN_HEADER

#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <tuple>
#include <math.h>

class ShapeStrategy : public sf::Shape
{
public:
    explicit ShapeStrategy(const u_int16_t point_count);
    virtual ~ShapeStrategy();
    virtual u_int16_t get_point_count() const;
    virtual void set_point_count(const u_int16_t point_count);
    virtual void set_size(const sf::Vector2f&) = 0;
    virtual const sf::Vector2f& get_size() = 0;
    virtual sf::Vector2f get_point(u_int16_t) const;
protected:
    u_int16_t point_count_;
};

class EllipceStrategy : public ShapeStrategy
{
public:
    explicit EllipceStrategy(const sf::Vector2f& radius = sf::Vector2f(0, 0), u_int16_t point_count = 30);
    virtual ~EllipceStrategy();
    void set_size(const sf::Vector2f& radius) override;
    const sf::Vector2f& get_size() override;
    sf::Vector2f get_point(u_int16_t index) const override;
protected:
    sf::Vector2f radius_;
};

class PuzzleSide
{
public:
    PuzzleSide(ShapeStrategy* s);
    ~PuzzleSide();
    void set_shape(ShapeStrategy* s);
    void set_point_count(u_int16_t point_count);
    u_int16_t get_point_count();
    void set_size(const sf::Vector2f& radius);
    const sf::Vector2f& get_size();
    virtual sf::Vector2f get_point(u_int16_t index) const;

private:
    ShapeStrategy* shapeStrategy_ = nullptr;
};

#endif