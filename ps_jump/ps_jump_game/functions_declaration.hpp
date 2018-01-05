#pragma once

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

//объявление функций и структур

// графика слайдов
struct GameScene
{
    int gameSlideId;  // id слайда
    int changePlayer; // id спрайта игрока
    int changeLevel;  // id уровня

    // фон окна
    sf::Texture screenFon;
    sf::Sprite screenSpriteFon;

    // спрайты игроков
    sf::Texture playerTexture1;
    sf::Sprite player1;
    sf::Texture playerTexture2;
    sf::Sprite player2;
    sf::Texture playerTexture3;
    sf::Sprite player3;

    // кнопки
    sf::RectangleShape buttonRight;
    sf::RectangleShape buttonLeft;

    // выделение выбора
    sf::RectangleShape borderPlayerChange;
    sf::RectangleShape borderLevelChange;

    // тескты
    sf::Font font;
    sf::Text textNext;
    sf::Text textBack;
    sf::Text textExit;
    sf::Text textStart;
    sf::Text textNewGame;
    sf::Text textMenu;
    sf::Text psJump;
    sf::Text level1;
    sf::Text level2;
    sf::Text level3;
};

void drawVisibleGameSlide(sf::RenderWindow &window, GameScene &scene);            // выбор слайда для прорисовки
void eventAnalisis(sf::RenderWindow &window, GameScene &scene, sf::Event &event); // анализ события для определенного слайда

void caseGamestatus1(sf::RenderWindow &window, GameScene &scene, sf::Event &event); // события на первом слайде
void caseGamestatus2(sf::RenderWindow &window, GameScene &scene, sf::Event &event); // события на втором слайде
void caseGamestatus3(sf::RenderWindow &window, GameScene &scene, sf::Event &event); // события на третьем слайде
void caseGamestatus5(sf::RenderWindow &window, GameScene &scene, sf::Event &event); // события на пятом слайде

void draw1(sf::RenderWindow &window, GameScene &scene); // рисуем первый слайд
void draw2(sf::RenderWindow &window, GameScene &scene); // рисуем второй слайд
void draw3(sf::RenderWindow &window, GameScene &scene); // рисуем третий слайд
void draw5(sf::RenderWindow &window, GameScene &scene); // рисуем пятый слайд

void elementInitialisation(sf::RenderWindow &window, GameScene &scene); // инициализация элементов структуры
void splashScreen(sf::RenderWindow &window, GameScene &scene);          //грузим первый слайд
void slidePlayerChoice(sf::RenderWindow &window, GameScene &scene);     //грузим слайд выбора персонажа
void slideLevelChoice(sf::RenderWindow &window, GameScene &scene);      // грузим слайд выбора уровня
void resultOfGame(sf::RenderWindow &window, GameScene &scene);          //грузим результат

void updatePlay(sf::RenderWindow &window, int &changePlayer, int &changeLevel); // игра началась
