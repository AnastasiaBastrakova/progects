#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

struct Arrow
{
    sf::ConvexShape pointer;
    void update(sf::Vector2f MousePosition, float time);
    void initialization(sf::Vector2f position);
    sf::Vector2f toMove(float currentAngle, float time);
    void draw(sf::RenderWindow &Window);
};

void Arrow::initialization(sf::Vector2f position)
{
    pointer.setFillColor(sf::Color(88, 88, 88));
    pointer.setOutlineThickness(1);
    pointer.setOutlineColor(sf::Color(0, 0, 0));
    pointer.setPosition(position);

    pointer.setPointCount(7);
    pointer.setRotation(0);
    pointer.setScale(-1, 1);

    pointer.setPoint(0, {0, -40});
    pointer.setPoint(1, {0, -20});
    pointer.setPoint(2, {50, -20});
    pointer.setPoint(3, {50, 20});
    pointer.setPoint(4, {0, 20});
    pointer.setPoint(5, {0, 40});
    pointer.setPoint(6, {-50, 0});
}

void Arrow::draw(sf::RenderWindow &Window)
{
    Window.draw(pointer);
}

int main()
{
    // все, что связано с окном
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop1.1", sf::Style::Default, settings);

    // стрелка
    Arrow pointer;
    pointer.initialization(sf::Vector2f({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color(255, 255, 255));
        pointer.draw(window);
        window.display();
    }
}