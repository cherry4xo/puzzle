#include <SFML/Graphics.hpp>
#include <cmath>
#include "pattern.hpp"
#include <iostream>
#include <numbers>
#include <cmath>

enum class CircleRotation
{
    top,
    bottom,
    left,
    right
};

inline std::vector<sf::Vector2f> getCirclePoints(CircleRotation crot)
{
    std::vector<sf::Vector2f> ret;
    const u_int16_t maxpoints = 30;
    const float radius = 200.f;
    for(size_t i = 0; i < maxpoints + 1; ++i)
    {
        sf::Vector2f point;
        switch(crot)
        {
            case CircleRotation::bottom:
                point = radius * sf::Vector2f(std::cos(M_PI * i / maxpoints), std::sin(M_PI * i / maxpoints));
                break;
            case CircleRotation::top:
                point = radius * sf::Vector2f(std::cos(M_PI * i / maxpoints), std::sin(-M_PI * i / maxpoints));
                break;
            case CircleRotation::left:
                point = radius * sf::Vector2f(std::sin(-M_PI * i / maxpoints), std::cos(M_PI * i / maxpoints));
                break;
            case CircleRotation::right:
                point = radius * sf::Vector2f(std::sin(M_PI * i / maxpoints), std::cos(M_PI * i / maxpoints));
                break;
        }

        ret.push_back(point);
    }

    return ret;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(800u, 600), "Circle");
    app.setFramerateLimit(60);
    // sf::CircleShape circle(100.f);
    // circle.setFillColor(sf::Color::Magenta);
    const sf::Vector2f mid = sf::Vector2f(app.getSize()) / 2.f;
    // circle.setPosition(mid - sf::Vector2f(circle.getRadius(), circle.getRadius()));

    while(app.isOpen())
    {
        sf::Event e;
        while(app.pollEvent(e))
            if(e.type == sf::Event::Closed)
                app.close();

        app.clear();
        sf::VertexArray arr(sf::TriangleFan);
        sf::Vertex start = mid;
        start.color = sf::Color{201, 105, 220, 255};
        arr.append(start);
        for(sf::Vector2f v : getCirclePoints(CircleRotation::right))
        {   
            sf::Vertex circle_vertex = sf::Vector2f(mid + v);
            circle_vertex.color = sf::Color{201, 105, 220, 255};
            arr.append(circle_vertex);
        }
        // app.draw(circle);
        sf::Vertex finish = mid;
        finish.color = sf::Color{201, 105, 220, 255};
        arr.append(finish);
        app.draw(arr);
        app.display();
    }

    return 0;
}