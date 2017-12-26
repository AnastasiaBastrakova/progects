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

void initBalls(std::vector<sf::CircleShape> &balls, std::vector<sf::Vector2f> &speed, PRNG &generator, sf::Texture &font2, int num)
{
    balls[num].setOutlineThickness(5);
    balls[num].setOutlineColor(sf::Color(255, 255, 255, 50));
    int color1 = (random(generator, 0, 256));
    int color2 = (random(generator, 0, 256));
    int color3 = (random(generator, 0, 256));
    balls[num].setRadius(random(generator, 20, 60));
    balls[num].setTexture(&font2);
    balls[num].setTextureRect(sf::IntRect(1, 1, 2 * balls[num].getRadius(), 2 * balls[num].getRadius()));
    balls[num].setFillColor(sf::Color(color1, color2, color3));
    balls[num].setOrigin({balls[num].getRadius(), balls[num].getRadius()});
    speed[num].x = (random(generator, 0, 500)) - 250.f;
    speed[num].y = (random(generator, 0, 500)) - 250.f;
    float x = random(generator, balls[num].getRadius(), WINDOW_WIDTH - balls[num].getRadius());
    float y = random(generator, balls[num].getRadius(), WINDOW_HEIGHT - balls[num].getRadius());
    balls[num].setPosition({x, y});
    int flag = 1;
    while ((std::size(balls) >= 2) && (flag == 1))
    {
        flag = 0;
        for (int i = 0; i < (num - 1); ++i)
        {
            while (std::hypotf((balls[i].getPosition().x - balls[num].getPosition().x), (balls[i].getPosition().y - balls[num].getPosition().y)) <= (balls[i].getRadius() + balls[num].getRadius()))
            {
                float x = random(generator, balls[num].getRadius(), WINDOW_WIDTH - balls[num].getRadius());
                float y = random(generator, balls[num].getRadius(), WINDOW_HEIGHT - balls[num].getRadius());
                balls[num].setPosition({x, y});
                flag = 1;
                std::cout << num << std::endl;
            }
        }
    }
}

void update(std::vector<sf::CircleShape> &balls, std::vector<sf::Vector2f> &speed, sf::RenderWindow &window, float time)
{
    for (int k = 1; k < 30; ++k)
    {
        sf::Vector2f minStep;
        sf::Vector2f newBallPos;
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
            minStep = speed[i] * time / 30.f;
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

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop2.5 Rarely balls are created one above one", sf::Style::Default, settings);

    sf::Sprite spriteFont;
    sf::Texture font1;
    font1.loadFromFile("images/font.jpg");
    spriteFont.setTexture(font1);
    spriteFont.setPosition(0, 0);

    sf::Texture font2;
    font2.loadFromFile("images/planet.jpg");

    PRNG generator;
    initGenerator(generator);

    sf::Clock clock;
    float time;

    int num = -1;

    std::vector<sf::CircleShape> balls;
    std::vector<sf::Vector2f> speed;
    std::vector<sf::Clock> lifetime;

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
            case sf::Event::MouseButtonPressed:
                if (event.key.code == sf::Mouse::Left)
                {
                    ++num;
                    balls.push_back(sf::CircleShape());
                    speed.push_back(sf::Vector2f());
                    initBalls(balls, speed, generator, font2, num);
                }
                break;
            default:
                break;
            }
        }
        time = clock.restart().asSeconds();

        update(balls, speed, window, time);
        redrawFrame(window, balls, spriteFont);
    }
}
