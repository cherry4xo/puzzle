#pragma once

#ifndef PATTERN_HEADER
#define PATTERN_HEADER

#include <SFML/Graphics.hpp>
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
    virtual u_int16_t get_point_count() const;
    virtual void set_point_count(const u_int16_t point_count);
    virtual void set_size(const sf::Vector2f&) = 0;
    virtual const sf::Vector2f& get_size() = 0;
    virtual inline std::vector<sf::Vector2f> getPoints() = 0;
protected:
    u_int16_t point_count_;
    std::vector<sf::Vector2f> points_;
    const Rotation srot_;
};

class EllipceStrategy : public ShapeStrategy
{
public:
    explicit EllipceStrategy(const sf::Vector2f& radius = sf::Vector2f(0, 0), 
                            u_int16_t point_count = 30, 
                            const Rotation srot, 
                            const sf::Vector2f& position = sf::Vector2f(0, 0));
    virtual ~EllipceStrategy();
    void set_size(const sf::Vector2f& radius) override;
    const sf::Vector2f& get_size() override;
    inline std::vector<sf::Vector2f> getPoints() override;
    void update();
    void draw(sf::RenderWindow* window);
protected:
    sf::Vector2f radius_;
    sf::Vector2f position_;
    sf::VertexArray* shape_ = nullptr;
};

class PuzzleSide
{
public:
    PuzzleSide(ShapeStrategy* s);
    virtual ~PuzzleSide() = default;
    void set_shape(ShapeStrategy* s);
    void set_point_count(u_int16_t point_count);
    u_int16_t get_point_count();
    void set_size(const sf::Vector2f& radius);
    const sf::Vector2f& get_size();
    void draw();
protected:
    ShapeStrategy* shapeStrategy_ = nullptr;
};

#endif