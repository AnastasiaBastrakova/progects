#include "functions_declaration.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// игра началась
void updatePlay(sf::RenderWindow &window, GameScene &scene)
{
    switch (scene.changeLevel)
    {
    case 1:
        scene.screenFon.loadFromFile("images/nonono.jpg");
        break;
    case 2:
        scene.screenFon.loadFromFile("images/ccc.jpg");
        break;
    case 3:
        scene.screenFon.loadFromFile("images/momomo.jpg");
        break;
    default:
        break;
    }
    // грузим графику начала игры
    scene.screenSpriteFon.setTexture(scene.screenFon);
    window.setTitle("Let's Jump!");
    int isGameOver = 0;

    sf::Clock clock;

    while (isGameOver = 0)
    {
    }
}