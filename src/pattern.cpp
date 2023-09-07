#include "pattern.hpp"

ShapeStrategy::ShapeStrategy(const u_int16_t point_count): point_count_(point_count) {}
ShapeStrategy::~ShapeStrategy () {}

u_int16_t ShapeStrategy::get_point_count() const 
{
    return point_count_;
}
void ShapeStrategy::set_point_count(const u_int16_t point_count)
{
    point_count_ = point_count;
}

EllipceStrategy::EllipceStrategy(const sf::Vector2f& radius = sf::Vector2f(0, 0), u_int16_t point_count = 30)
    : radius_(radius), ShapeStrategy(point_count) {}
EllipceStrategy::~EllipceStrategy() {}
void EllipceStrategy::set_size(const sf::Vector2f& radius)
{
    radius_ = radius;
    update();
}
const sf::Vector2f& EllipceStrategy::get_size() { return radius_; }
sf::Vector2f EllipceStrategy::get_point(u_int16_t index) const
{
    static const float pi = M_PI;
    float angle = index * 2 * pi / get_point_count() - pi / 2;
    float x = std::cos(angle) * radius_.x;
    float y = std::sin(angle) * radius_.y;

    return sf::Vector2f(radius_.x + x, radius_.y + y);
}

PuzzleSide::PuzzleSide(ShapeStrategy* s) : shapeStrategy_(s) {}
PuzzleSide::~PuzzleSide() { delete shapeStrategy_; }
void PuzzleSide::set_shape(ShapeStrategy* s) 
{
    if (shapeStrategy_)
        delete shapeStrategy_;
    shapeStrategy_ = s;
}
void PuzzleSide::set_point_count(u_int16_t point_count)
{
    shapeStrategy_->set_point_count(point_count);
}
u_int16_t PuzzleSide::get_point_count()
{
    return shapeStrategy_->get_point_count();
}
void PuzzleSide::set_size(const sf::Vector2f& size)
{
    shapeStrategy_->set_size(size);
}
const sf::Vector2f& PuzzleSide::get_size()
{
    return shapeStrategy_->get_size();
}
sf::Vector2f PuzzleSide::get_point(u_int16_t index) const
{
    return shapeStrategy_->get_point(index);
}