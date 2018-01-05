#include "functions_declaration.hpp"
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
#include <sstream>
#include <string>

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

// игра началась
void updatePlay(sf::RenderWindow &window, int &changePlayer, int &changeLevel)
{
    // генератор случайных чисел
    PRNG generator;
    initGenerator(generator);

    // загрузка графики в зависимости от уровня и игрока
    GameStyle styleOfGame;
    downloadGraphics(window, changePlayer, changeLevel, styleOfGame); // грузим графику игры (в style_of_game.cpp)

    // объявление переменных
    int isGameOver = 0;
    float speedY = -400;
    float g = 400;
    float deltaTime;
    float scoreOfPlay = 0;

    // инициализация платформ
    std::vector<sf::RectangleShape> platform(12);

    for (int i = 0; i < std::size(platform); ++i)
    {
        platform[i].setSize({100, 25});
        platform[i].setFillColor(sf::Color(0, 0, 0, 90));
        platform[i].setOutlineThickness(2);
    }

    platform[1].setPosition(350, 550);
    platform[2].setPosition(500, 450);
    platform[3].setPosition(100, 350);
    platform[4].setPosition(300, 250);
    platform[5].setPosition(50, 150);
    platform[6].setPosition(400, 50);
    platform[7].setPosition(500, 500);
    platform[8].setPosition(100, 400);
    platform[9].setPosition(230, 300);
    platform[10].setPosition(600, 200);
    platform[11].setPosition(370, 100);
    platform[12].setPosition(300, 325);

    // линии состояния
    styleOfGame.topLeftLine.setSize({596, 30});
    styleOfGame.topLeftLine.setFillColor(sf::Color(0, 0, 0));
    styleOfGame.topLeftLine.setOutlineThickness(2);
    styleOfGame.topLeftLine.setPosition(2, 2);

    styleOfGame.topRightLine.setSize({296, 30});
    styleOfGame.topRightLine.setFillColor(sf::Color(0, 0, 0));
    styleOfGame.topRightLine.setOutlineThickness(2);
    styleOfGame.topRightLine.setPosition(598, 2);

    styleOfGame.font.loadFromFile("a_MachinaOrtoSls_Bold.ttf");
    styleOfGame.score.setFont(styleOfGame.font);

    // часы
    sf::Clock clock;

    while (isGameOver == 0)
    {
        std::ostringstream playerScoreString;
        for (int i = 0; i < std::size(platform); ++i)
        {
            if (platform[i].getPosition().y >= 700)
            {
                platform[i].setPosition(random(generator, 0, 700), platform[i].getPosition().y - 700);
            }
        }

        deltaTime = clock.restart().asSeconds();

        for (int i = 0; i < std::size(platform); ++i)
        {
            if ((styleOfGame.player.getPosition().x > platform[i].getPosition().x - 35) &&
                (styleOfGame.player.getPosition().x < platform[i].getPosition().x + 135) &&
                (styleOfGame.player.getPosition().y < platform[i].getPosition().y - 45) &&
                (styleOfGame.player.getPosition().y > platform[i].getPosition().y - 51) && (speedY > 0))
            {
                speedY = -400;
            }
        }

        if ((styleOfGame.player.getPosition().y <= 300) && (speedY <= 0))
        {
            speedY = speedY + g * deltaTime;
            for (int i = 0; i < std::size(platform); ++i)
            {
                platform[i].setPosition(platform[i].getPosition().x, platform[i].getPosition().y - speedY * deltaTime);
            }
            styleOfGame.player.setPosition(styleOfGame.player.getPosition().x, styleOfGame.player.getPosition().y);

            scoreOfPlay = round(scoreOfPlay + speedY * deltaTime);
        }
        else if (styleOfGame.player.getPosition().y >= 600)
        {
            isGameOver = 1;
        }
        else
        {
            speedY = speedY + g * deltaTime;
            styleOfGame.player.setPosition(styleOfGame.player.getPosition().x, styleOfGame.player.getPosition().y + speedY * deltaTime);
            scoreOfPlay = round(scoreOfPlay);
        }

        sf::Event event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            if (styleOfGame.player.getPosition().x + 35 <= 800)
            {
                styleOfGame.player.setPosition(styleOfGame.player.getPosition().x + 600 * deltaTime, styleOfGame.player.getPosition().y);
                styleOfGame.player.setScale(-0.75, 0.75);
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            if (styleOfGame.player.getPosition().x - 35 >= 0)
            {
                styleOfGame.player.setPosition(styleOfGame.player.getPosition().x - 600 * deltaTime, styleOfGame.player.getPosition().y);
                styleOfGame.player.setScale(0.75, 0.75);
            }

        playerScoreString << -scoreOfPlay;                               //формируем строку
        styleOfGame.score.setString("Score:" + playerScoreString.str()); //вызываем сформированную выше строку методом .str()
        styleOfGame.score.setPosition(600, 3);

        draw4(window, styleOfGame, platform);
    }
}
