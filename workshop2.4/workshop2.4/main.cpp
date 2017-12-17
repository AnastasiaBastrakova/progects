#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <algorithm>
#include <SFML/Window.hpp>
#include <vector>
#include <random>
#include <cassert>
#include <ctime>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

void initBalls(std::vector<sf::CircleShape> &balls, std::vector<sf::Vector2f> &speed, PRNG &generator, sf::Texture &font2)
{
    for (int i = 0; i < std::size(balls); ++i)
    {
        balls[i].setOutlineThickness(1);
        balls[i].setOutlineColor(sf::Color(255, 255, 255, 50));
        int color1 = (random(generator, 0, 256));
        int color2 = (random(generator, 0, 256));
        int color3 = (random(generator, 0, 256));
        balls[i].setRadius(random(generator, 20, 60));
        balls[i].setTexture(&font2);
        balls[i].setTextureRect(sf::IntRect(1, 1, 2 * balls[i].getRadius(), 2 * balls[i].getRadius()));
        balls[i].setFillColor(sf::Color(color1, color2, color3));
        speed[i].x = (random(generator, 0, 500)) - 250.f;
        speed[i].y = (random(generator, 0, 500)) - 250.f;
        balls[i].setOrigin({balls[i].getRadius(), balls[i].getRadius()});
        float x = random(generator, balls[i].getRadius(), WINDOW_WIDTH - balls[i].getRadius());
        float y = random(generator, balls[i].getRadius(), WINDOW_HEIGHT - balls[i].getRadius());
        balls[i].setPosition({x, y});
    }
}

void update(std::vector<sf::CircleShape> &balls, std::vector<sf::Vector2f> &speed, sf::RenderWindow &window, float time)
{
    sf::Vector2f minStep;
    sf::Vector2f newBallPos;
    for (int k = 0; k < 5; ++k)
    {
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
            minStep = speed[i] * time / 5.f;
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
                newBallPos.x = balls[i].getRadius();
            }
            balls[i].setPosition(newBallPos);
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<sf::CircleShape> balls, sf::Sprite spriteFont)
{
    window.clear(sf::Color(0, 0, 0, 0));
    window.draw(spriteFont);
    for (int i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i]);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop2.3", sf::Style::Default, settings);

    sf::Sprite spriteFont;
    sf::Texture font1;
    font1.loadFromFile("images/font.jpg");
    spriteFont.setTexture(font1);
    spriteFont.setPosition(0, 0);

    sf::Texture font2;
    font2.loadFromFile("images/planet.jpg");

    PRNG generator;
    initGenerator(generator);

    std::vector<sf::CircleShape> balls(5);
    std::vector<sf::Vector2f> speed(5);

    sf::Clock clock;
    float time;

    initBalls(balls, speed, generator, font2);

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
        float time = clock.restart().asSeconds();

        update(balls, speed, window, time);
        redrawFrame(window, balls, spriteFont);
    }
}
