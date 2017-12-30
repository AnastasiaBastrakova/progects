#include "functions_declaration.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// считываем события
void handleEvents(sf::RenderWindow &window, GameScene &scene)
{
    sf::Event event;
    eventAnalisis(window, scene, event); // анализ события для определенного слайда (в case_gamestatus.cpp)
}

// обноваляем окно
void render(sf::RenderWindow &window, GameScene &scene)
{
    window.clear();
    drawVisibleGameSlide(window, scene); // выбор слайда для прорисовки (в case_gamestatus.cpp)
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "PS Jump Game", sf::Style::Titlebar, settings);

    GameScene scene;                      // графика игры (в function_declaration.hpp)
    elementInitialisation(window, scene); // инициализация элементов структуры (в load_slide.cpp)

    splashScreen(window, scene); //грузим первый слайд (в load_slide.cpp)

    while (window.isOpen())
    {
        handleEvents(window, scene); // считываем события (в main.cpp)
        render(window, scene);       // обноваляем окно (в main.cpp)
    }
}