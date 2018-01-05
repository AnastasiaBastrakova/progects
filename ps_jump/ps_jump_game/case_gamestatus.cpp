#include "functions_declaration.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>

//определение слайда на котором мы находимся и перенаправление

// выбор слайда для прорисовки
void drawVisibleGameSlide(sf::RenderWindow &window, GameScene &scene)
{
    switch (scene.gameSlideId)
    {
    case 1:
        draw1(window, scene);
        break;
    case 2:
        draw2(window, scene);
        break;
    case 3:
        draw3(window, scene);
        break;
    case 5:
        draw5(window, scene);
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
            caseGamestatus1(window, scene, event); // события на первом слайде (в case_gamestatus_slide)
            break;
        case 2:
            caseGamestatus2(window, scene, event); // события на втором слайде (в case_gamestatus_slide)
            break;
        case 3:
            caseGamestatus3(window, scene, event); // события на третьем слайде (в case_gamestatus_slide)
            break;
        case 5:
            caseGamestatus5(window, scene, event); // события на пятом слайде (в case_gamestatus_slide)
            break;
        default:
            break;
        }
    }
}