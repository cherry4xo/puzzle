#include <SFML/Graphics.hpp>
#include <cmath>
#include "pattern.hpp"
#include "puzzle.hpp"
#include "picture.hpp"
#include "algorithm.hpp"
#include <iostream>
#include <numbers>
#include <cmath>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(1920u, 1080), "Circle", sf::Style::Fullscreen);
    app.setFramerateLimit(60);
    const sf::Vector2f mid = sf::Vector2f(app.getSize()) / 2.f;

    Algorithm algo(20, 20, "media/bw.png");
    algo.setDefaultPositionAllPuzzle();

    while(app.isOpen())
    {
        sf::Event e;
        while(app.pollEvent(e)){
            if(e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
        }
        app.clear();
        algo.drawAllPuzzle(&app);
        app.display();
    }

    return 0;
}