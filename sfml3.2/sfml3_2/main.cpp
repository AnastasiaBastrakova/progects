#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Window.hpp>

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

initEllipse(sf::ConvexShape &ellipse, sf::Vector2f position)
{
    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {60.f, 100.f};

    ellipse.setPosition({position.x, position.y});
    ellipse.setFillColor(sf::Color(255, 255, 255));
    ellipse.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }
}

initEye(sf::ConvexShape &eye, sf::Vector2f position)
{
    constexpr int pointCount = 200;
    const sf::Vector2f eyeRadius = {12.f, 20.f};

    eye.setPosition({position.x, position.y});
    eye.setFillColor(sf::Color(0, 0, 0));
    eye.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        eye.setPoint(pointNo, point);
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &eye, sf::Vector2f posEye)
{
    sf::Vector2f circleOrbit = {30, 50};
    const sf::Vector2f delta = mousePosition - posEye;
    const float cursorAngle = atan2(delta.y, delta.x);
    eye.setPosition(posEye.x + circleOrbit.x * std::cos(cursorAngle), posEye.y + circleOrbit.y * std::sin(cursorAngle));
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "It's my eyes when I did that work", sf::Style::Default, settings);

    sf::ConvexShape ellipse1;
    sf::ConvexShape ellipse2;
    sf::ConvexShape eye1;
    sf::ConvexShape eye2;

    sf::Vector2f posEye1 = {480, 300};
    sf::Vector2f posEye2 = {320, 300};

    sf::Vector2f mousePosition;

    initEllipse(ellipse1, posEye1);
    initEllipse(ellipse2, posEye2);

    initEye(eye1, posEye1);
    initEye(eye2, posEye2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                onMouseMove(event.mouseMove, mousePosition);
                break;
            default:
                break;
            }
        }
        update(mousePosition, eye1, posEye1);
        update(mousePosition, eye2, posEye2);

        window.clear();
        window.draw(ellipse1);
        window.draw(ellipse2);
        window.draw(eye1);
        window.draw(eye2);
        window.display();
    }
}