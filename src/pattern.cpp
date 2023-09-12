#include "pattern.hpp"

ShapeStrategy::ShapeStrategy(const u_int16_t point_count, const Rotation srot): point_count_(point_count), srot_(srot) {}
ShapeStrategy::~ShapeStrategy () {}

u_int16_t ShapeStrategy::get_point_count() const 
{
    return point_count_;
}
void ShapeStrategy::set_point_count(const u_int16_t point_count)
{
    point_count_ = point_count;
}

EllipceStrategy::EllipceStrategy(const sf::Vector2f& radius = sf::Vector2f(0, 0), 
                                u_int16_t point_count = 30, 
                                const Rotation srot,
                                const sf::Vector2f& position = sf::Vector2f(0, 0))
    : radius_(radius), ShapeStrategy(point_count, srot), position_(position) {}
EllipceStrategy::~EllipceStrategy() {}
void EllipceStrategy::set_size(const sf::Vector2f& radius)
{
    radius_ = radius;
    update();
}
const sf::Vector2f& EllipceStrategy::get_size() { return radius_; }

inline std::vector<sf::Vector2f> EllipceStrategy::getPoints()
{
    std::vector<sf::Vector2f> ret;
    for(size_t i = 0; i < point_count_ + 1; ++i)
    {
        sf::Vector2f point;
        switch(srot_)
        {
            case Rotation::top:
                // point = radius_ * sf::Vector2f(std::cos(M_PI * i / point_count_), std::sin(-M_PI * i / point_count_));
                point = sf::Vector2f(radius_.x * std::cos(M_PI * i / point_count_), radius_.y * std::sin(-M_PI * i / point_count_));
                break;
            case Rotation::bottom:
                point = sf::Vector2f(radius_.x * std::cos(M_PI * i / point_count_), radius_.y * std::sin(-M_PI * i / point_count_));
                break;
            case Rotation::left:
                point = sf::Vector2f(radius_.x * std::cos(M_PI * i / point_count_), radius_.y * std::sin(-M_PI * i / point_count_));
                break;
            case Rotation::right:
                point = sf::Vector2f(radius_.x * std::cos(M_PI * i / point_count_), radius_.y * std::sin(-M_PI * i / point_count_));
                break;
        }
        ret.push_back(point);
    }

    points_ = ret;
}

void EllipceStrategy::update()
{
    sf::VertexArray arr(sf::TriangleFan);
    sf::Vertex start = this->position_;
    start.color = sf::Color(255, 255, 255, 0);
    arr.append(start);
    for(sf::Vector2f v : getPoints())
    {
        sf::Vertex vertex = sf::Vector2f(position_ + v);
        vertex.color = sf::Color(255, 255, 255, 0);
        arr.append(vertex);
    }
    sf::Vertex finish = this->position_;
    finish.color = sf::Color(255, 255, 255, 0);
    arr.append(finish);

    *shape_ = arr;
}

void EllipceStrategy::draw(sf::RenderWindow* window)
{
    window->draw(*shape_);
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

void PuzzleSide::draw()
{
    
}