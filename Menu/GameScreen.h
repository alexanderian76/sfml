// MainMenuScreen.hpp
#pragma once
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "Menu.h"
#include <iostream>
#include "../PlayerController.h"
#include "../GlobalObjects.h"
#include "../Enemy/EnemySpawner.h"

class GameScreen : public Screen
{
private:
    PlayerController player;
    Sprite *playerSprite;
    sf::Texture backgroundTexture, enemyTexture;
    EnemySpawner *spawner;
    Clock clock;
    Sprite *background;
    SoundBuffer buffer;
    Sound *sound;

public:
    GameScreen()
    {
        buffer.loadFromFile("test.wav");
        sound = new Sound(buffer);
        sound->play();

        backgroundTexture.loadFromFile("696.jpg");

        background = new Sprite(backgroundTexture);
        screenType = 2;
        clock.start();
        Texture t("./01_idle/idle_1.png");
        playerSprite = new Sprite(t);

        playerSprite->setOrigin({playerSprite->getLocalBounds().size.x / 2, playerSprite->getLocalBounds().size.y / 2});
        playerSprite->setPosition({250, 150});

        // TODO
        // Утечка с текстурой, исправить потом для нормального рендера
        if (!enemyTexture.loadFromFile("./01_idle/idle_1.png"))
        {
            std::cerr << "Failed to load enemy texture!" << std::endl;
            throw;
        }
        spawner = new EnemySpawner(enemyTexture);
        spawner->setSpawnRate(1.5f); // Спавн каждые 1.5 секунды
        spawner->setMaxEnemies(15);
    }

    void handleInput(const sf::Event &event, sf::RenderWindow &window) override
    {
        if (event.is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (event.is<Event::KeyReleased>())
        {
            if (player.getMotion() == 3 || player.getMotion() == 2 || player.getMotion() == 4 || player.getMotion() == 5)
            {

                clock.restart();
                player.setMotion(0);
            }
        }
        // key pressed
        else if (event.is<sf::Event::KeyPressed>())
        {

            const auto *keyPressed = event.getIf<sf::Event::KeyPressed>();

            std::cout << (int)keyPressed->scancode << std::endl;

            if (keyPressed->scancode == Keyboard::Scancode::B && player.getMotion() != 1)
            {
                clock.restart();
                player.setMotion(1);
            }

            if (keyPressed->scancode == Keyboard::Scancode::D && player.getMotion() != 2)
            {
                player.setMotion(2);
            }

            if (keyPressed->scancode == Keyboard::Scancode::A && player.getMotion() != 3)
            {
                player.setMotion(3);
            }

            if (keyPressed->scancode == Keyboard::Scancode::W && player.getMotion() != 4)
            {
                player.setMotion(4);
            }

            if (keyPressed->scancode == Keyboard::Scancode::S && player.getMotion() != 5)
            {
                player.setMotion(5);
            }
            // std::cout << appEvent << std::endl;
        }
    }

    void update(sf::Time deltaTime) override
    {
        // Обновление логики меню (анимации и т.д.)
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(*background);

        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            window.draw(GlobalObjects::objects[i].drawObject());
        }
        spawner->update(clock.getElapsedTime().asSeconds(), *playerSprite);
        spawner->draw(window);

        for (auto &enemy : spawner->getEnemies())
        {
            if (FloatRect(enemy->getPosition(), {enemy->xPadding, enemy->yPadding}).findIntersection(FloatRect({playerSprite->getPosition().x + player.direction * (player.xPadding / (player.direction > 0 ? 1 : 2)), playerSprite->getPosition().y}, {1, player.yPadding / 2})))
            {
                // Здесь нужно обрабатывать урон игроку
                // Например: player.takeDamage(enemy->damage);
                if (player.isAttack)
                {
                    enemy->takeDamage(10);
                }
            }
        }

        player.DrawPlayer(clock, playerSprite, window);

        if (sound->getStatus() == Sound::Status::Stopped)
        {
            sound->getCone();
        }
    }

    void onEnter() override
    {
        std::cout << "Entering main menu" << std::endl;
    }

    void onExit() override
    {
        std::cout << "Exiting game screen" << std::endl;
    }

    void handleMenuInput(const sf::Event &event, sf::RenderWindow &window)
    {
    }
    ~GameScreen() override
    {
        std::cout << "DELETE GAME SCREEN" << std::endl;
        delete spawner;
        delete playerSprite;
        delete background;
        delete sound;
    }
};