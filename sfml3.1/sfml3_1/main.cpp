#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Window.hpp>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

void OnMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &MousePosition)
{
    MousePosition = {float(event.x), float(event.y)};
    std::cout << "mouse x = " << event.x << ", y = " << event.y << std::endl;
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float time)
{
    std::cout << std::endl;
    //угол курсора
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float cursorAngle = atan2(delta.y, delta.x);
    float degreesCursorAngle = (toDegrees(cursorAngle));
    if (degreesCursorAngle < 0)
    {
        degreesCursorAngle = 360 + degreesCursorAngle;
    }
    std::cout << "degreesCursorAngle = " << degreesCursorAngle << std::endl;

    //угол стрелки
    const float pointerDegreesAngle = pointer.getRotation();
    std::cout << "pointerDegreesAngle = " << pointerDegreesAngle << std::endl;

    //дельта угол между курсором и стрелкой
    float deltaAngle = degreesCursorAngle - pointerDegreesAngle;
    if (deltaAngle > 180)
    {
        deltaAngle = deltaAngle - 360;
    }
    else if (deltaAngle < -180)
    {
        deltaAngle = deltaAngle + 360;
    }
    std::cout << "deltaAngle = " << deltaAngle << std::endl;

    //максиматьный шаг за маленький кусочек времени с учетом направления
    const float maxAngleSpeed = 15;
    float speedRoute = 1;
    if (deltaAngle < 0)
    {
        speedRoute = -1;
    }
    float maxAngleRotation = speedRoute * time * maxAngleSpeed;

    float nextPointerAngle = 0;
    if (std::abs(deltaAngle) < std::abs(maxAngleRotation))
    {
        nextPointerAngle = pointer.getRotation() + deltaAngle;
        pointer.setRotation(nextPointerAngle);
    }
    else
    {
        nextPointerAngle = pointer.getRotation() + maxAngleRotation;
        pointer.setRotation(nextPointerAngle);
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    //окно
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop", sf::Style::Default, settings);

    //часы
    sf::Clock clock;

    //pointer И Mouseposition
    sf::Vector2f MousePosition;
    sf::ConvexShape pointer;
    init(pointer);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseMoved)
            {
                OnMouseMove(event.mouseMove, MousePosition);
            }
        }
        update(MousePosition, pointer, clock.restart().asSeconds());
        redrawFrame(window, pointer);
    }
}
