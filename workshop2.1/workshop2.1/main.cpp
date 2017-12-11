#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Window.hpp>
#include <vector>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop2.1");

    std::vector<sf::CircleShape> balls(5);
    std::vector<sf::Vector2f> speed(5);

    sf::Clock clock;
    float time;

    for (int i = 0; i < std::size(balls); ++i)
    {
        if (i == 0)
        {
            balls[i].setPosition({140.f, 100.f});
            speed[i] = {150.f, 70.f};
        }
        if (i == 1)
        {
            balls[i].setPosition({180.f, 500.f});
            speed[i] = {20.f, 10.f};
        }
        if (i == 2)
        {
            balls[i].setPosition({500.f, 240.f});
            speed[i] = {200.f, 15.f};
        }
        if (i == 3)
        {
            balls[i].setPosition({700.f, 20.f});
            speed[i] = {50.f, 140.f};
        }
        if (i == 4)
        {
            balls[i].setPosition({400.f, 300.f});
            speed[i] = {120.f, 120.f};
        }
        balls[i].setFillColor(sf::Color(24 * i, 50, 150));
        balls[i].setRadius(i * 10 + 20);
    }

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

        time = clock.restart().asSeconds();

        for (int i = 0; i < std::size(balls); ++i)
        {
            if ((balls[i].getPosition().y + 2 * balls[i].getRadius() >= WINDOW_HEIGHT) || (balls[i].getPosition().y <= 0))
            {
                speed[i] = {speed[i].x, -speed[i].y};
            }
            if ((balls[i].getPosition().x + 2 * balls[i].getRadius() >= WINDOW_WIDTH) || (balls[i].getPosition().x <= 0))
            {
                speed[i] = {-speed[i].x, speed[i].y};
            }

            sf::Vector2f newBall0Pos = balls[i].getPosition() + speed[i] * time;
            balls[i].setPosition(newBall0Pos);
        }

        window.clear();
        for (int i = 0; i < balls.size(); ++i)
        {
            window.draw(balls[i]);
        }
        window.display();
    }
}
