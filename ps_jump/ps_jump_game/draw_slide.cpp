#include "functions_declaration.hpp"
#include "gaming_functions_declaration.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

void draw1(sf::RenderWindow &window, GameScene &scene)
{
    window.draw(scene.screenSpriteFon);
    window.draw(scene.buttonLeft);
    window.draw(scene.buttonRight);
    window.draw(scene.textNext);
    window.draw(scene.textExit);
    window.draw(scene.psJump);
}

void draw2(sf::RenderWindow &window, GameScene &scene)
{
    window.draw(scene.screenSpriteFon);
    window.draw(scene.buttonRight);
    window.draw(scene.buttonLeft);
    window.draw(scene.textNext);
    window.draw(scene.textBack);
    window.draw(scene.borderPlayerChange);
    window.draw(scene.player1);
    window.draw(scene.player2);
    window.draw(scene.player3);
}

void draw3(sf::RenderWindow &window, GameScene &scene)
{
    window.draw(scene.screenSpriteFon);
    window.draw(scene.buttonRight);
    window.draw(scene.buttonLeft);
    window.draw(scene.textBack);
    window.draw(scene.textStart);
    window.draw(scene.borderLevelChange);
    window.draw(scene.level1);
    window.draw(scene.level2);
    window.draw(scene.level3);
}

void draw4(sf::RenderWindow &window, GameStyle &styleOfGame, std::vector<sf::RectangleShape> platform)
{
    window.clear();
    window.draw(styleOfGame.gameSpriteFon);
    for (int i = 0; i < std::size(platform); ++i)
    {
        window.draw(platform[i]);
    }
    window.draw(styleOfGame.topRightLine);
    window.draw(styleOfGame.topLeftLine);
    window.draw(styleOfGame.bottomLine);
    window.draw(styleOfGame.player);
    window.draw(styleOfGame.score);
    window.display();
}

void draw5(sf::RenderWindow &window, GameScene &scene)
{
    window.draw(scene.screenSpriteFon);
    window.draw(scene.buttonRight);
    window.draw(scene.buttonLeft);
    window.draw(scene.textMenu);
    window.draw(scene.textNewGame);
}