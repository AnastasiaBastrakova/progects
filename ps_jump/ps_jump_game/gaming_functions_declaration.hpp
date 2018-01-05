#pragma once

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

struct GameStyle
{
    // фон игры
    sf::Texture gameFon;
    sf::Sprite gameSpriteFon;

    // игрок
    sf::Texture playerTexture;
    sf::Sprite player;

    sf::Text score;
    sf::Font font;

    sf::RectangleShape topRightLine;
    sf::RectangleShape topLeftLine;
    sf::RectangleShape bottomLine;
};

void downloadGraphics(sf::RenderWindow &window, int &changePlayer, int &changeLevel, GameStyle &styleOfGame);

void draw4(sf::RenderWindow &window, GameStyle &styleOfGame, std::vector<sf::RectangleShape> platform); // рисуем четвертый слайд