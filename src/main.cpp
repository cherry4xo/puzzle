#include <SFML/Graphics.hpp>
#include <cmath>
#include "pattern.hpp"
#include <iostream>
#include <numbers>
#include <cmath>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(800u, 600), "Circle");
    app.setFramerateLimit(60);
    const sf::Vector2f mid = sf::Vector2f(app.getSize()) / 2.f;
    EllipceStrategy* ellipce = new EllipceStrategy(sf::Vector2f(100, 100), sf::Vector2f(200, 200), Rotation::top, 30);

    while(app.isOpen())
    {
        sf::Event e;
        while(app.pollEvent(e))
            if(e.type == sf::Event::Closed)
                app.close();

        app.clear();
        ellipce->update();
        ellipce->draw(&app);
        app.display();
    }

    return 0;
}