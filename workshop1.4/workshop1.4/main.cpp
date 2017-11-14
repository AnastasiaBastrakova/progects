#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <SFML/Window.hpp>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Workshop1.4 'А я бегу, бегу, бегу, бегу...'");

    //текстура кот
    sf::Texture cat;
    cat.loadFromFile("cat.png");

    sf::Sprite spriteCat;
    spriteCat.setTexture(cat);
    spriteCat.setPosition(400, 300);
    spriteCat.setScale(1, 1);
    spriteCat.setOrigin({15, 15});

    //текстура лазер
    sf::Texture laser;
    laser.loadFromFile("laser.png");

    sf::Sprite spriteLaser;
    spriteLaser.setTexture(laser);
    spriteLaser.setOrigin({15, 15});

    sf::Vector2i mousePosition;
    sf::Vector2f newPosition;

    bool isLaserVisible = false;
    bool isRealyTime = false;

    sf::Clock clock;
    float time;

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
                mousePosition = sf::Mouse::getPosition(window);
                std::cout << "mouse x = " << mousePosition.x << ", mouse y = " << mousePosition.y << std::endl;
                spriteLaser.setPosition(sf::Vector2f(mousePosition));
                isLaserVisible = true;
                if (not isRealyTime)
                {
                    time = clock.restart().asSeconds();
                    isRealyTime = true;
                }
                break;
            default:
                break;
            }
        }
        window.clear(sf::Color(255, 255, 255));
        window.draw(spriteCat);
        if ((isLaserVisible) && (isRealyTime))
        {

            //разность кота и лазера
            sf::Vector2f deltaVector = spriteLaser.getPosition() - spriteCat.getPosition();

            //маленький шаг
            time = clock.restart().asSeconds();
            const float maxSpeedCat = 1;
            sf::Vector2f maxStepCat = time * maxSpeedCat * deltaVector;

            //Шаги
            if (std::hypotf(deltaVector.x, deltaVector.y) > std::hypotf(maxStepCat.x, maxStepCat.y))
            {
                newPosition = spriteCat.getPosition() + maxStepCat;
                spriteCat.setPosition(newPosition);
                deltaVector = deltaVector - maxStepCat;
            }
            else if (std::hypotf(deltaVector.x, deltaVector.y) < std::hypotf(maxStepCat.x, maxStepCat.y))
            {
                newPosition = spriteLaser.getPosition();
                spriteCat.setPosition(newPosition);
            }

            if (maxStepCat.x > 0)
            {
                spriteCat.setScale(1, 1);
            }
            else
            {
                spriteCat.setScale(-1, 1);
            }

            window.draw(spriteLaser);
        }
        window.display();
    }
}
