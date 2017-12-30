#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//объявление функций и структур

// графика игры
struct GameScene
{
    int gameSlideId;
    int changePlayer;
    int changeLevel;

    sf::Texture screenFon;
    sf::Sprite screenSpriteFon;

    sf::Texture playerTexture1;
    sf::Sprite player1;
    sf::Texture playerTexture2;
    sf::Sprite player2;
    sf::Texture playerTexture3;
    sf::Sprite player3;

    sf::RectangleShape buttonRight;
    sf::RectangleShape buttonLeft;

    sf::RectangleShape borderPlayerChange;
    sf::RectangleShape borderLevelChange;

    sf::Font font;
    sf::Text textNext;
    sf::Text textBack;
    sf::Text textExit;
    sf::Text textStart;
    sf::Text psJump;
    sf::Text level1;
    sf::Text level2;
    sf::Text level3;
};

void drawVisibleGameSlide(sf::RenderWindow &window, GameScene &scene);            // выбор слайда для прорисовки
void eventAnalisis(sf::RenderWindow &window, GameScene &scene, sf::Event &event); // анализ события для определенного слайда

void elementInitialisation(sf::RenderWindow &window, GameScene &scene); // инициализация элементов структуры
void splashScreen(sf::RenderWindow &window, GameScene &scene);          //грузим первый слайд
void slidePlayerChoice(sf::RenderWindow &window, GameScene &scene);     //грузим слайд выбора персонажа
void slideLevelChoice(sf::RenderWindow &window, GameScene &scene);      // грузим слайд выбора уровня
void updatePlay(sf::RenderWindow &window, GameScene &scene);            // игра началась

//void splashScreenVisit(sf::RenderWindow &window, GameScene &scene);