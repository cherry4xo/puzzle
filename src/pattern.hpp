#pragma once

#ifndef PATTERN_HEADER
#define PATTERN_HEADER

#include <SFML/Graphics.hpp>
#include <sys/types.h>
#include <tuple>
#include <math.h>

class Strategy : public sf::Shape
{
public:
    explicit Strategy(const u_int16_t point_count)
        : point_count_(point_count) {}
    virtual ~Strategy() {}
    virtual u_int16_t get_point_count() const
    {
        return point_count_;
    }
    virtual void set_point_count(const u_int16_t point_count)
    {
        point_count_ = point_count;
    }
protected:
    u_int16_t point_count_;
};

class EllipceStrategy : public Strategy
{
public:
    explicit EllipceStrategy(const sf::Vector2f& radius = sf::Vector2f(0, 0), u_int16_t point_count = 30)
        : radius_(radius), Strategy(point_count) { update(); }
    virtual ~EllipceStrategy() {}
    void set_radius(const sf::Vector2f& radius)
    {
        radius_ = radius;
        update();
    }
    const sf::Vector2f& get_radius() 
    {
        return radius_;
    }
    virtual sf::Vector2f get_point(u_int16_t index) const
    {
        static const float pi = M_PI;
        float angle = index * 2 * pi / get_point_count() - pi / 2;
        float x = std::cos(angle) * radius_.x;
        float y = std::sin(angle) * radius_.y;

        return sf::Vector2f(radius_.x + x, radius_.y + y);
    }
protected:
    sf::Vector2f radius_;
};

class CircleStrategy : public Strategy
{
public:
    CircleStrategy(const float radius = 0, const u_int16_t point_count = 30)
        : radius_(radius), Strategy(point_count) {}
    virtual ~CircleStrategy() {}
    void set_radius(const float radius)
    {
        radius_ = radius;
        update();
    }
    const float get_radius()
    {
        return radius_;
    }
    virtual sf::Vector2f get_point(u_int16_t index) const
    {
        static const float pi = M_PI;
        float angle = index * 2 * pi / get_point_count() - pi / 2;
        float x = std::cos(angle) * radius_;
        float y = std::sin(angle) * radius_;

        return sf::Vector2f(radius_ + x, radius_ + y);
    }
protected:
    float radius_;
};

class Context
{
public:
    
private:
    
};

class PuzzleSideBuilder
{
public:
    PuzzleSideBuilder() {}
};

#endif