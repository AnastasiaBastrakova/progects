#include "functions_declaration.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//изначальная графика слайдов

//грузим первый слайд (доработать)
void splashScreen(sf::RenderWindow &window, GameScene &scene)
{
    // fon, title
    scene.screenFon.loadFromFile("images/fon5.jpg");
    scene.screenSpriteFon.setTexture(scene.screenFon);
    window.setTitle("Let's Jump!");
}

//грузим слайд выбора персонажа
void slidePlayerChoice(sf::RenderWindow &window, GameScene &scene)
{
    // fon, title
    scene.screenFon.loadFromFile("images/mramor.jpg");
    scene.screenSpriteFon.setTexture(scene.screenFon);
    window.setTitle("Secect player!");
}

void slideLevelChoice(sf::RenderWindow &window, GameScene &scene)
{
    // fon, title
    scene.screenFon.loadFromFile("images/lamp.jpg");
    scene.screenSpriteFon.setTexture(scene.screenFon);
    window.setTitle("Select level");
}

// инициализация элементов структуры
void elementInitialisation(sf::RenderWindow &window, GameScene &scene)
{
    scene.gameSlideId = 1;
    scene.changeLevel = 1;

    // players
    scene.playerTexture1.loadFromFile("images/beebig.png");
    scene.player1.setTexture(scene.playerTexture1);
    scene.player1.setPosition(150, 250);

    scene.playerTexture2.loadFromFile("images/tenbig.png");
    scene.player2.setTexture(scene.playerTexture2);
    scene.player2.setPosition(350, 250);

    scene.playerTexture3.loadFromFile("images/boobig.png");
    scene.player3.setTexture(scene.playerTexture3);
    scene.player3.setPosition(550, 250);

    //buttons
    scene.buttonRight.setSize({200, 50});
    scene.buttonRight.setPosition(450, 450);
    scene.buttonRight.setFillColor(sf::Color(0, 0, 0, 90));
    scene.buttonRight.setOutlineThickness(2);

    scene.buttonLeft.setSize({200, 50});
    scene.buttonLeft.setPosition(150, 450);
    scene.buttonLeft.setFillColor(sf::Color(0, 0, 0, 90));
    scene.buttonLeft.setOutlineThickness(2);

    scene.borderPlayerChange.setSize({100, 100});
    scene.borderPlayerChange.setFillColor(sf::Color(0, 0, 0, 90));
    scene.borderPlayerChange.setOutlineThickness(2);
    scene.borderPlayerChange.setPosition(scene.player1.getPosition());

    scene.borderLevelChange.setSize({200, 50});
    scene.borderLevelChange.setFillColor(sf::Color(0, 0, 0, 90));
    scene.borderLevelChange.setOutlineThickness(2);
    scene.borderLevelChange.setPosition(150, 200);

    //buttons text
    scene.font.loadFromFile("a_MachinaOrtoSls_Bold.ttf");

    scene.textNext.setFont(scene.font);
    scene.textNext.setString("Next =>");
    scene.textNext.setPosition(510, 455);
    scene.textNext.setCharacterSize(28);
    scene.textNext.setFillColor(sf::Color::Red);
    scene.textNext.setStyle(sf::Text::Underlined);

    scene.textExit.setFont(scene.font);
    scene.textExit.setString(">< Exit");
    scene.textExit.setPosition(210, 455);
    scene.textExit.setCharacterSize(28);
    scene.textExit.setFillColor(sf::Color::Red);
    scene.textExit.setStyle(sf::Text::Underlined);

    scene.psJump.setFont(scene.font);
    scene.psJump.setString("{ PS Jump }");
    scene.psJump.setPosition(300, 220);
    scene.psJump.setCharacterSize(45);
    scene.psJump.setFillColor(sf::Color::Red);
    scene.psJump.setStyle(sf::Text::Underlined);

    scene.textBack.setFont(scene.font);
    scene.textBack.setString("<= Back");
    scene.textBack.setPosition(210, 455);
    scene.textBack.setCharacterSize(28);
    scene.textBack.setFillColor(sf::Color::Red);
    scene.textBack.setStyle(sf::Text::Underlined);

    scene.textStart.setFont(scene.font);
    scene.textStart.setString("Start $");
    scene.textStart.setPosition(510, 455);
    scene.textStart.setCharacterSize(28);
    scene.textStart.setFillColor(sf::Color::Red);
    scene.textStart.setStyle(sf::Text::Underlined);

    scene.level1.setFont(scene.font);
    scene.level1.setString("Level 'Laig'");
    scene.level1.setPosition(150, 200);
    scene.level1.setCharacterSize(28);
    scene.level1.setFillColor(sf::Color::Red);
    scene.level1.setStyle(sf::Text::Underlined);

    scene.level2.setFont(scene.font);
    scene.level2.setString("Level 'C++'");
    scene.level2.setPosition(150, 280);
    scene.level2.setCharacterSize(28);
    scene.level2.setFillColor(sf::Color::Red);
    scene.level2.setStyle(sf::Text::Underlined);

    scene.level3.setFont(scene.font);
    scene.level3.setString("Level 'Iip'");
    scene.level3.setPosition(150, 360);
    scene.level3.setCharacterSize(28);
    scene.level3.setFillColor(sf::Color::Red);
    scene.level3.setStyle(sf::Text::Underlined);
}