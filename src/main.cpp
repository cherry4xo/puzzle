// #include <iostream>
// #include <SFML/Graphics.hpp>

// int main(int argc, char** argv)
// {
//     sf::VertexArray triangle(sf::TrianglesStrip, 4);

//     triangle[0].position = sf::Vector2f(0.0f, 0.0f);
//     triangle[1].position = sf::Vector2f(0.0f, 600.0f);
//     triangle[2].position = sf::Vector2f(800.0f, 0.0f);
//     triangle[3].position = sf::Vector2f(800.0f, 600.0f);
//     triangle[0].color = sf::Color(0xff, 0xff, 0xff, 0xff);
//     triangle[1].color = sf::Color(0xff, 0xff, 0xff, 0xff);
//     triangle[2].color = sf::Color(0xff, 0xff, 0xff, 0xff);
//     triangle[3].color = sf::Color(0xff, 0xff, 0xff, 0xff);

//     sf::Texture tex;
//     if (!tex.loadFromFile("../src/media/unicorn_picture.bmp"))
//     {
//         std::cout << "Cannot load from file\n";
//     }

//     float tw = tex.getSize().x;
//     float th = tex.getSize().y;

//     triangle[0].texCoords = sf::Vector2f(0.0f, 0.0f);
//     triangle[1].texCoords = sf::Vector2f(0.0f, th);
//     triangle[2].texCoords = sf::Vector2f(tw, 0.0f);
//     triangle[3].texCoords = sf::Vector2f(tw, th);

//     sf::RenderStates rs;
//     rs.texture = &tex;
//     // rs.blendMode = sf::BlendNone;

//     sf::ContextSettings settings;
//     settings.antialiasingLevel = 8;

//     sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

//     while(window.isOpen())
//     {
//         sf::Event e;
//         while(window.pollEvent(e))
//             if(e.type == sf::Event::Closed)
//                 window.close();
//         window.clear();
//         window.draw(triangle, rs);
//         window.display();
//     }
//     return 0;
// }

#include <SFML/Graphics.hpp>
#include <cmath>
#include "pattern.hpp"
#include "puzzle.hpp"
#include "picture.hpp"
#include <iostream>
#include <numbers>
#include <cmath>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow app(sf::VideoMode(1920u, 1080), "Circle");
    app.setFramerateLimit(60);
    const sf::Vector2f mid = sf::Vector2f(app.getSize()) / 2.f;

    Puzzle* puzzle = new Puzzle(new PuzzleSize(10, 10), "media/image.png");
    puzzle->initMatrix(new PuzzleSide(new EllipceStrategy(sf::Vector2f(25, 25), sf::Vector2f(100, 100), Rotation::top, 30)),
                       new PuzzleSide(new EllipceStrategy(sf::Vector2f(25, 25), sf::Vector2f(200, 200), Rotation::bottom, 30)),
                       new PuzzleSide(new EllipceStrategy(sf::Vector2f(25, 25), sf::Vector2f(300, 300), Rotation::left, 30)),
                       new PuzzleSide(new EllipceStrategy(sf::Vector2f(25, 25), sf::Vector2f(400, 400), Rotation::right, 30)));
    puzzle->parcePicture();
    puzzle->matrixToTree();
    puzzle->puzzleTree->puzzle()->setBodyPosition(sf::Vector2f(mid.x - puzzle->puzzleTree->puzzle()->getSize().x / 2, 
                                                               mid.y - puzzle->puzzleTree->puzzle()->getSize().y / 2));
    puzzle->puzzleTree->right()->puzzle()->setBodyPosition(sf::Vector2f(mid.x - puzzle->puzzleTree->puzzle()->getSize().x / 2 + 200, 
                                                                        mid.y - puzzle->puzzleTree->puzzle()->getSize().y / 2));
    puzzle->puzzleTree->right()->right()->puzzle()->setBodyPosition(sf::Vector2f(mid.x - puzzle->puzzleTree->puzzle()->getSize().x / 2 + 400, 
                                                                                 mid.y - puzzle->puzzleTree->puzzle()->getSize().y / 2));
    puzzle->getMatrix()[0][0]->setBodyPosition(sf::Vector2f(mid.x - puzzle->puzzleTree->puzzle()->getSize().x / 2, 
                                                            mid.y - puzzle->puzzleTree->puzzle()->getSize().y / 2));
    puzzle->getMatrix()[0][1]->setBodyPosition(sf::Vector2f(mid.x - puzzle->puzzleTree->puzzle()->getSize().x / 2 + 200, 
                                                            mid.y - puzzle->puzzleTree->puzzle()->getSize().y / 2));
    puzzle->getMatrix()[0][2]->setBodyPosition(sf::Vector2f(mid.x - puzzle->puzzleTree->puzzle()->getSize().x / 2 + 400, 
                                                            mid.y - puzzle->puzzleTree->puzzle()->getSize().y / 2));
    // std::cout << puzzle->getMatrix()[0][0]->getTopSide()->
    while(app.isOpen())
    {
        sf::Event e;
        while(app.pollEvent(e)){
            if(e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
        }
        app.clear();
        // puzzle->getMatrix()[0][0]->update();
        // puzzle->getMatrix()[0][1]->update();
        // puzzle->getMatrix()[0][2]->update();
        // puzzle->getMatrix()[0][0]->draw(&app);
        // puzzle->getMatrix()[0][1]->draw(&app);
        // puzzle->getMatrix()[0][2]->draw(&app);
        puzzle->puzzleTree->puzzle()->update();
        puzzle->puzzleTree->right()->puzzle()->update();
        puzzle->puzzleTree->right()->right()->puzzle()->update();
        puzzle->puzzleTree->puzzle()->draw(&app);
        puzzle->puzzleTree->right()->puzzle()->draw(&app);
        puzzle->puzzleTree->right()->right()->puzzle()->draw(&app);
        app.display();
    }

    return 0;
}