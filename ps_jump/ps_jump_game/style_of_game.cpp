#include "gaming_functions_declaration.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <algorithm>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <cassert>
#include <ctime>
#include <iostream>

void downloadGraphics(sf::RenderWindow &window, int &changePlayer, int &changeLevel, GameStyle &styleOfGame)
{
    // фон
    switch (changeLevel)
    {
    case 1:
        styleOfGame.gameFon.loadFromFile("images/nonono.jpg");
        break;
    case 2:
        styleOfGame.gameFon.loadFromFile("images/ccc.jpg");
        break;
    case 3:
        styleOfGame.gameFon.loadFromFile("images/momomo.jpg");
        break;
    default:
        break;
    }
    styleOfGame.gameSpriteFon.setTexture(styleOfGame.gameFon);
    //заголовок
    window.setTitle("Let's Jump!");

    // игрок
    switch (changePlayer)
    {
    case 1:
        styleOfGame.playerTexture.loadFromFile("images/beebig.png");
        break;
    case 2:
        styleOfGame.playerTexture.loadFromFile("images/tenbig.png");
        break;
    case 3:
        styleOfGame.playerTexture.loadFromFile("images/boobig.png");
        break;
    default:
        break;
    }
    styleOfGame.player.setTexture(styleOfGame.playerTexture);
    styleOfGame.player.setOrigin(35, 35);
    styleOfGame.player.setScale(0.7, 0.7);
    styleOfGame.player.setPosition(400, 500);
}
