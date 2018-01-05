#include "functions_declaration.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

// события на первом слайде
void caseGamestatus1(sf::RenderWindow &window, GameScene &scene, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if ((mousePosition.x > scene.buttonRight.getPosition().x) &&
            (mousePosition.x < scene.buttonRight.getPosition().x + scene.buttonRight.getSize().x) &&
            (mousePosition.y > scene.buttonRight.getPosition().y) &&
            (mousePosition.y < scene.buttonRight.getPosition().y + scene.buttonRight.getSize().y))
        {
            scene.gameSlideId = 2;
            slidePlayerChoice(window, scene); //грузим слайд выбора персонажа (в load_slide.cpp)
        }
        else if ((mousePosition.x > scene.buttonLeft.getPosition().x) &&
                 (mousePosition.x < scene.buttonLeft.getPosition().x + scene.buttonLeft.getSize().x) &&
                 (mousePosition.y > scene.buttonLeft.getPosition().y) &&
                 (mousePosition.y < scene.buttonLeft.getPosition().y + scene.buttonLeft.getSize().y))
        {
            window.close();
        }
    }
}

// события на втором слайде
void caseGamestatus2(sf::RenderWindow &window, GameScene &scene, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if ((mousePosition.x > scene.buttonLeft.getPosition().x) &&
            (mousePosition.x < scene.buttonLeft.getPosition().x + scene.buttonLeft.getSize().x) &&
            (mousePosition.y > scene.buttonLeft.getPosition().y) &&
            (mousePosition.y < scene.buttonLeft.getPosition().y + scene.buttonLeft.getSize().y))
        {
            scene.gameSlideId = 1;
            splashScreen(window, scene); //грузим первый слайд (в load_slide.cpp)
        }
        else if ((mousePosition.x > scene.buttonRight.getPosition().x) &&
                 (mousePosition.x < scene.buttonRight.getPosition().x + scene.buttonRight.getSize().x) &&
                 (mousePosition.y > scene.buttonRight.getPosition().y) &&
                 (mousePosition.y < scene.buttonRight.getPosition().y + scene.buttonRight.getSize().y))
        {
            scene.gameSlideId = 3;
            slideLevelChoice(window, scene); //грузим слайд выбора уровня (в load_slide.cpp)
        }
        if ((mousePosition.x > scene.player1.getPosition().x) &&
            (mousePosition.x < scene.player1.getPosition().x + 100) &&
            (mousePosition.y > scene.player1.getPosition().y) &&
            (mousePosition.y < scene.player1.getPosition().y + 100))
        {
            scene.changePlayer = 1;
        }
        else if ((mousePosition.x > scene.player2.getPosition().x) &&
                 (mousePosition.x < scene.player2.getPosition().x + 100) &&
                 (mousePosition.y > scene.player2.getPosition().y) &&
                 (mousePosition.y < scene.player2.getPosition().y + 100))
        {
            scene.changePlayer = 2;
        }
        else if ((mousePosition.x > scene.player3.getPosition().x) &&
                 (mousePosition.x < scene.player3.getPosition().x + 100) &&
                 (mousePosition.y > scene.player3.getPosition().y) &&
                 (mousePosition.y < scene.player3.getPosition().y + 100))
        {
            scene.changePlayer = 3;
        }
        switch (scene.changePlayer)
        {
        case 1:
            scene.borderPlayerChange.setPosition(scene.player1.getPosition());
            break;
        case 2:
            scene.borderPlayerChange.setPosition(scene.player2.getPosition());
            break;
        case 3:
            scene.borderPlayerChange.setPosition(scene.player3.getPosition());
            break;
        default:
            break;
        }
    }
}

// события на третьем слайде
void caseGamestatus3(sf::RenderWindow &window, GameScene &scene, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if ((mousePosition.x > scene.level1.getPosition().x) &&
            (mousePosition.x < scene.level1.getPosition().x + 300) &&
            (mousePosition.y > scene.level1.getPosition().y) &&
            (mousePosition.y < scene.level1.getPosition().y + 100))
        {
            scene.changeLevel = 1;
            scene.borderLevelChange.setPosition(scene.level1.getPosition());
        }
        else if ((mousePosition.x > scene.level2.getPosition().x) &&
                 (mousePosition.x < scene.level2.getPosition().x + 300) &&
                 (mousePosition.y > scene.level2.getPosition().y) &&
                 (mousePosition.y < scene.level2.getPosition().y + 100))
        {
            scene.changeLevel = 2;
            scene.borderLevelChange.setPosition(scene.level2.getPosition());
        }
        else if ((mousePosition.x > scene.level3.getPosition().x) &&
                 (mousePosition.x < scene.level3.getPosition().x + 300) &&
                 (mousePosition.y > scene.level3.getPosition().y) &&
                 (mousePosition.y < scene.level3.getPosition().y + 100))
        {
            scene.changeLevel = 3;
            scene.borderLevelChange.setPosition(scene.level3.getPosition());
        }
        if ((mousePosition.x > scene.buttonLeft.getPosition().x) &&
            (mousePosition.x < scene.buttonLeft.getPosition().x + scene.buttonLeft.getSize().x) &&
            (mousePosition.y > scene.buttonLeft.getPosition().y) &&
            (mousePosition.y < scene.buttonLeft.getPosition().y + scene.buttonLeft.getSize().y))
        {
            scene.gameSlideId = 2;
            slidePlayerChoice(window, scene); //грузим слайд выбора персонажа (в load_slide.cpp)
        }
        else if ((mousePosition.x > scene.buttonRight.getPosition().x) &&
                 (mousePosition.x < scene.buttonRight.getPosition().x + scene.buttonRight.getSize().x) &&
                 (mousePosition.y > scene.buttonRight.getPosition().y) &&
                 (mousePosition.y < scene.buttonRight.getPosition().y + scene.buttonRight.getSize().y))
        {
            scene.gameSlideId = 4;
            updatePlay(window, scene.changePlayer, scene.changeLevel); // игра началаь (в main_update_play.cpp)
            scene.gameSlideId = 5;
            resultOfGame(window, scene); //грузим результат (в load_slide.cpp)
        }
    }
}

// события на пятом слайде
void caseGamestatus5(sf::RenderWindow &window, GameScene &scene, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if ((mousePosition.x > scene.buttonRight.getPosition().x) &&
            (mousePosition.x < scene.buttonRight.getPosition().x + scene.buttonRight.getSize().x) &&
            (mousePosition.y > scene.buttonRight.getPosition().y) &&
            (mousePosition.y < scene.buttonRight.getPosition().y + scene.buttonRight.getSize().y))
        {
            scene.gameSlideId = 4;
            updatePlay(window, scene.changePlayer, scene.changeLevel); // игра началаь (в main_update_play.cpp)
            scene.gameSlideId = 5;
            resultOfGame(window, scene); //грузим результат (в load_slide.cpp)
        }
        if ((mousePosition.x > scene.buttonLeft.getPosition().x) &&
            (mousePosition.x < scene.buttonLeft.getPosition().x + scene.buttonLeft.getSize().x) &&
            (mousePosition.y > scene.buttonLeft.getPosition().y) &&
            (mousePosition.y < scene.buttonLeft.getPosition().y + scene.buttonLeft.getSize().y))
        {
            scene.gameSlideId = 1;
            splashScreen(window, scene); //грузим первый слайд (в load_slide.cpp)
        }
    }
}