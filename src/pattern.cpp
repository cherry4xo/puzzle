#include "pattern.hpp"

ShapeStrategy::ShapeStrategy(const u_int16_t point_count, const Rotation srot): point_count_(point_count), srot_(srot) {}
ShapeStrategy::~ShapeStrategy () {}

size_t ShapeStrategy::getPointCount() const 
{
    return point_count_;
}

void ShapeStrategy::set_point_count(const u_int16_t point_count)
{
    point_count_ = point_count;
}

sf::Vector2f ShapeStrategy::getPoint(size_t index) const
{
    sf::Vector2f point;
    switch(srot_)
    {
        case Rotation::top:
            // point = radius_ * sf::Vector2f(std::cos(M_PI * i / point_count_), std::sin(-M_PI * i / point_count_));
            point = sf::Vector2f(std::cos(M_PI * index / point_count_), std::sin(-M_PI * index / point_count_));
            break;
        case Rotation::bottom:
            point = sf::Vector2f(std::cos(M_PI * index / point_count_), std::sin(M_PI * index / point_count_));
            break;
        case Rotation::left:
            point = sf::Vector2f(std::sin(-M_PI * index / point_count_), std::cos(M_PI * index / point_count_));
            break;
        case Rotation::right:
            point = sf::Vector2f(std::sin(M_PI * index / point_count_), std::cos(M_PI * index / point_count_));
            break;
    }
    return point;
}

EllipceStrategy::EllipceStrategy(const sf::Vector2f& radius, 
                                const sf::Vector2f& position,
                                const Rotation srot,
                                u_int16_t point_count = 30)
    : ShapeStrategy(point_count, srot), radius_(radius) 
    { this->setPosition(position); }
EllipceStrategy::~EllipceStrategy() {}
void EllipceStrategy::set_size(const sf::Vector2f& radius)
{
    radius_ = radius;
    update();
}
const sf::Vector2f& EllipceStrategy::get_size() { return radius_; }

inline void EllipceStrategy::getPoints()
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
                point = sf::Vector2f(radius_.x * std::cos(M_PI * i / point_count_), radius_.y * std::sin(M_PI * i / point_count_));
                break;
            case Rotation::left:
                point = sf::Vector2f(radius_.x * std::sin(-M_PI * i / point_count_), radius_.y * std::cos(M_PI * i / point_count_));
                break;
            case Rotation::right:
                point = sf::Vector2f(radius_.x * std::sin(M_PI * i / point_count_), radius_.y * std::cos(M_PI * i / point_count_));
                break;
        }
        ret.push_back(point);
    }

    points_ = ret;
}  

void EllipceStrategy::update()
{
    sf::VertexArray* arr = new sf::VertexArray(sf::TriangleFan);
    sf::Vertex start = this->getPosition();
    start.color = sf::Color(255, 255, 255, 255);
    arr->append(start);
    this->getPoints();
    for(sf::Vector2f v : points_)
    {
        sf::Vertex vertex = sf::Vector2f(this->getPosition() + v);
        vertex.color = sf::Color(255, 255, 255, 255);
        arr->append(vertex);
    }
    sf::Vertex finish = this->getPosition();
    finish.color = sf::Color(255, 255, 255, 255);
    arr->append(finish);

    shape_ = arr;
}

void EllipceStrategy::draw(sf::RenderWindow* window)
{
    window->draw(*shape_);
}



PuzzleSide::PuzzleSide(ShapeStrategy* s) : shapeStrategy_(s) { shapeStrategy_->update(); }
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
size_t PuzzleSide::getPointCount()
{
    return shapeStrategy_->getPointCount();
}
void PuzzleSide::set_size(const sf::Vector2f& size)
{
    shapeStrategy_->set_size(size);
}
const sf::Vector2f& PuzzleSide::get_size()
{
    return shapeStrategy_->get_size();
}

void PuzzleSide::setPosition(sf::Vector2f position)
{
    shapeStrategy_->setPosition(position);
}

void PuzzleSide::update()
{
    shapeStrategy_->update();
}

void PuzzleSide::draw(sf::RenderWindow* window) 
{
    shapeStrategy_->draw(window);
}