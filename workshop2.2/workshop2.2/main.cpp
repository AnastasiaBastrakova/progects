#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <cassert>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop2.2");

    std::vector<sf::CircleShape> balls(5);
    std::vector<sf::Vector2f> speed(5);

    sf::Clock clock;
    float time;

    sf::Vector2f minStep;
    sf::Vector2f newBallPos;

    for (int i = 0; i < std::size(balls); ++i)
    {
        if (i == 0)
        {
            balls[i].setPosition({140.f, 1000.f});
            speed[i] = {150.f, 70.f};
        }
        if (i == 1)
        {
            balls[i].setPosition({180.f, 500.f});
            speed[i] = {2000.f, 100.f};
        }
        if (i == 2)
        {
            balls[i].setPosition({500.f, 2400.f});
            speed[i] = {200.f, 150.f};
        }
        if (i == 3)
        {
            balls[i].setPosition({650.f, 700.f});
            speed[i] = {50.f, 140.f};
        }
        if (i == 4)
        {
            balls[i].setPosition({400.f, 300.f});
            speed[i] = {-120.f, 120.f};
        }
        balls[i].setFillColor(sf::Color(24 * i, 50, 150));
        balls[i].setRadius(i * 10 + 20);
        balls[i].setOrigin({balls[i].getRadius(), balls[i].getRadius()});
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
            for (int j = i + 1; j < std::size(balls); ++j)
            {
                if (std::hypotf((balls[i].getPosition().x - balls[j].getPosition().x), (balls[i].getPosition().y - balls[j].getPosition().y)) <= (balls[i].getRadius() + balls[j].getRadius()))
                {
                    sf::Vector2f speedDifference1 = speed[i] - speed[j];
                    sf::Vector2f positionDifference1 = {balls[i].getPosition().x - balls[j].getPosition().x, balls[i].getPosition().y - balls[j].getPosition().y};
                    sf::Vector2f speedDifference2 = speed[j] - speed[i];
                    sf::Vector2f positionDifference2 = {balls[j].getPosition().x - balls[i].getPosition().x, balls[j].getPosition().y - balls[i].getPosition().y};
                    float scalarPr1 = speedDifference1.x * positionDifference1.x + speedDifference1.y * positionDifference1.y;
                    float scalarPr2 = positionDifference2.x * speedDifference2.x + positionDifference2.y * speedDifference2.y;
                    speed[i] = speed[i] - positionDifference1 * (scalarPr1 / ((std::hypotf(positionDifference1.x, positionDifference1.y)) * (std::hypotf(positionDifference1.x, positionDifference1.y))));
                    speed[j] = speed[j] - positionDifference2 * (scalarPr2 / ((std::hypotf(positionDifference2.x, positionDifference2.y)) * (std::hypotf(positionDifference2.x, positionDifference2.y))));
                }
            }
        }

        for (int i = 0; i < std::size(balls); ++i)
        {
            minStep = speed[i] * time / 2.f;
            newBallPos = balls[i].getPosition() + minStep;

            if (balls[i].getPosition().y + balls[i].getRadius() > WINDOW_HEIGHT)
            {
                speed[i].y = -fabs(speed[i].y);
                newBallPos.y = WINDOW_HEIGHT - balls[i].getRadius();
            }
            if (balls[i].getPosition().y - balls[i].getRadius() < 0)
            {
                speed[i].y = fabs(speed[i].y);
                newBallPos.y = balls[i].getRadius();
            }
            if (balls[i].getPosition().x + balls[i].getRadius() > WINDOW_WIDTH)
            {
                speed[i].x = -fabs(speed[i].x);
                newBallPos.x = WINDOW_WIDTH - balls[i].getRadius();
            }
            if (balls[i].getPosition().x - balls[i].getRadius() < 0)
            {
                speed[i].x = fabs(speed[i].x);
                speed[i].y = fabs(speed[i].y);
                newBallPos.x = balls[i].getRadius();
            }
            balls[i].setPosition(newBallPos);
        }

        window.clear();
        for (int i = 0; i < balls.size(); ++i)
        {
            window.draw(balls[i]);
        }
        window.display();
    }
}
