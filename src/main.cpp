#include <SFML/Graphics.hpp>
#include <cmath>
#include "pattern.hpp"
#include "puzzle.hpp"
#include <iostream>
#include <numbers>
#include <cmath>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(800u, 600), "Circle");
    app.setFramerateLimit(60);
    // const sf::Vector2f mid = sf::Vector2f(app.getSize()) / 2.f;
    PuzzleSide* side = new PuzzleSide(new EllipceStrategy(sf::Vector2f(100, 100), sf::Vector2f(100, 100), Rotation::top, 30));

    DefaultPuzzleBuilder* builder = new DefaultPuzzleBuilder(sf::Vector2f(100, 100));

    Director puzzleDirector(builder);
    puzzleDirector.construct(new PuzzleSide(new EllipceStrategy(sf::Vector2f(100, 100), sf::Vector2f(100, 100), Rotation::top, 30)),
                            new PuzzleSide(new EllipceStrategy(sf::Vector2f(100, 100), sf::Vector2f(200, 200), Rotation::bottom, 30)),
                            new PuzzleSide(new EllipceStrategy(sf::Vector2f(100, 100), sf::Vector2f(300, 300), Rotation::left, 30)),
                            new PuzzleSide(new EllipceStrategy(sf::Vector2f(100, 100), sf::Vector2f(400, 400), Rotation::right, 30)));

    while(app.isOpen())
    {
        sf::Event e;
        while(app.pollEvent(e))
            if(e.type == sf::Event::Closed)
                app.close();

        app.clear();
        // side->update();
        // side->draw(&app);
        puzzleDirector.update();
        puzzleDirector.draw(&app);
        app.display();
    }

    return 0;
}