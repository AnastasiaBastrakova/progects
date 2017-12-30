#include "functions_declaration.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//определение слайда на котором мы находимся и перенаправление

// выбор слайда для прорисовки
void drawVisibleGameSlide(sf::RenderWindow &window, GameScene &scene)
{
    switch (scene.gameSlideId)
    {
    case 1:
        window.draw(scene.screenSpriteFon);
        window.draw(scene.buttonLeft);
        window.draw(scene.buttonRight);
        window.draw(scene.textNext);
        window.draw(scene.textExit);
        window.draw(scene.psJump);
        break;
    case 2:
        window.draw(scene.screenSpriteFon);
        window.draw(scene.buttonRight);
        window.draw(scene.buttonLeft);
        window.draw(scene.textNext);
        window.draw(scene.textBack);
        window.draw(scene.borderPlayerChange);
        window.draw(scene.player1);
        window.draw(scene.player2);
        window.draw(scene.player3);
        break;
    case 3:
        window.draw(scene.screenSpriteFon);
        window.draw(scene.buttonRight);
        window.draw(scene.buttonLeft);
        window.draw(scene.textBack);
        window.draw(scene.textStart);
        window.draw(scene.borderLevelChange);
        window.draw(scene.level1);
        window.draw(scene.level2);
        window.draw(scene.level3);
        break;
    case 4:
        window.draw(scene.screenSpriteFon);
        break;
    case 5:
        break;
    default:
        break;
    }
}

// анализ события для определенного слайда
void eventAnalisis(sf::RenderWindow &window, GameScene &scene, sf::Event &event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        switch (scene.gameSlideId)
        {
        case 1:
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
                if ((mousePosition.x > scene.buttonLeft.getPosition().x) &&
                    (mousePosition.x < scene.buttonLeft.getPosition().x + scene.buttonLeft.getSize().x) &&
                    (mousePosition.y > scene.buttonLeft.getPosition().y) &&
                    (mousePosition.y < scene.buttonLeft.getPosition().y + scene.buttonLeft.getSize().y))
                {
                    window.close();
                }
            }
            break;
        case 2:
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
                if ((mousePosition.x > scene.buttonRight.getPosition().x) &&
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
                if ((mousePosition.x > scene.player2.getPosition().x) &&
                    (mousePosition.x < scene.player2.getPosition().x + 100) &&
                    (mousePosition.y > scene.player2.getPosition().y) &&
                    (mousePosition.y < scene.player2.getPosition().y + 100))
                {
                    scene.changePlayer = 2;
                }
                if ((mousePosition.x > scene.player3.getPosition().x) &&
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
            break;
        case 3:
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if ((mousePosition.x > scene.buttonLeft.getPosition().x) &&
                    (mousePosition.x < scene.buttonLeft.getPosition().x + scene.buttonLeft.getSize().x) &&
                    (mousePosition.y > scene.buttonLeft.getPosition().y) &&
                    (mousePosition.y < scene.buttonLeft.getPosition().y + scene.buttonLeft.getSize().y))
                {
                    scene.gameSlideId = 2;
                    slidePlayerChoice(window, scene); //грузим слайд выбора персонажа (в load_slide.cpp)
                }
                if ((mousePosition.x > scene.buttonRight.getPosition().x) &&
                    (mousePosition.x < scene.buttonRight.getPosition().x + scene.buttonRight.getSize().x) &&
                    (mousePosition.y > scene.buttonRight.getPosition().y) &&
                    (mousePosition.y < scene.buttonRight.getPosition().y + scene.buttonRight.getSize().y))
                {
                    scene.gameSlideId = 4;
                    updatePlay(window, scene); //гигра началаь (в main_update_play.cpp)
                }
                if ((mousePosition.x > scene.level1.getPosition().x) &&
                    (mousePosition.x < scene.level1.getPosition().x + 300) &&
                    (mousePosition.y > scene.level1.getPosition().y) &&
                    (mousePosition.y < scene.level1.getPosition().y + 100))
                {
                    scene.changeLevel = 1;
                }
                if ((mousePosition.x > scene.level2.getPosition().x) &&
                    (mousePosition.x < scene.level2.getPosition().x + 300) &&
                    (mousePosition.y > scene.level2.getPosition().y) &&
                    (mousePosition.y < scene.level2.getPosition().y + 100))
                {
                    scene.changeLevel = 2;
                }
                if ((mousePosition.x > scene.level3.getPosition().x) &&
                    (mousePosition.x < scene.level3.getPosition().x + 300) &&
                    (mousePosition.y > scene.level3.getPosition().y) &&
                    (mousePosition.y < scene.level3.getPosition().y + 100))
                {
                    scene.changeLevel = 3;
                }
                switch (scene.changeLevel)
                {
                case 1:
                    scene.borderLevelChange.setPosition(scene.level1.getPosition());
                    break;
                case 2:
                    scene.borderLevelChange.setPosition(scene.level2.getPosition());
                    break;
                case 3:
                    scene.borderLevelChange.setPosition(scene.level3.getPosition());
                    break;
                default:
                    break;
                }
            }
            break;
        case 5:
            break;
        default:
            break;
        }
    }
}