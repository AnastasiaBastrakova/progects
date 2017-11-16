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
};

void initialization(sf::ConvexShape &pointer)
{
    pointer.setPosition(400, 300);

    pointer.setFillColor(sf::Color(255, 255, 200));
    pointer.setOutlineThickness(1);
    pointer.setOutlineColor(sf::Color(0, 0, 0));

    pointer.setPointCount(7);
    pointer.setRotation(0);
    pointer.setOrigin({0, 0});
    pointer.setScale(-1, 1);

    pointer.setPoint(0, {0, -40});
    pointer.setPoint(1, {0, -20});
    pointer.setPoint(2, {50, -20});
    pointer.setPoint(3, {50, 20});
    pointer.setPoint(4, {0, 20});
    pointer.setPoint(5, {0, 40});
    pointer.setPoint(6, {-50, 0});
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(pointer);
    window.display();
}

void OnMouseMove(sf::Event::MouseMoveEvent &event, sf::Vector2f &MousePosition)
{
    MousePosition = {float(event.x), float(event.y)};
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float time)
{

    //угол курсора
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float cursorAngle = atan2(delta.y, delta.x);
    float degreesCursorAngle = (toDegrees(cursorAngle));
    if (degreesCursorAngle < 0)
    {
        degreesCursorAngle = 360 + degreesCursorAngle;
    }

    //угол стрелки
    const float pointerDegreesAngle = pointer.getRotation();

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

    //максиматьный шаг за маленький кусочек времени с учетом направления
    const float maxAngleSpeed = 90;
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

    float maxSpeed = 50;
    sf::Vector2f uniteVextor = delta / std::hypotf(delta.x, delta.y);
    sf::Vector2f stepVector = maxSpeed * time * uniteVextor;

    if (std::hypotf(delta.x, delta.y) > std::hypotf(stepVector.x, stepVector.y))
    {
        sf::Vector2f newPosition = pointer.getPosition() + stepVector;
        pointer.setPosition(newPosition);
    }
    else
    {
        pointer.setPosition(mousePosition);
    }
}

int main()
{
    // все, что связано с окном
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop1.1", sf::Style::Default, settings);

    //часы
    sf::Clock clock;

    // стрелка  и позиция мыши
    sf::ConvexShape pointer;
    initialization(pointer);
    sf::Vector2f MousePosition;

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