// MainMenuScreen.hpp
#pragma once
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "Menu.h"
#include <iostream>
#include "../PlayerController.h"
#include "../GlobalObjects.h"
#include "../Enemy/EnemySpawner.h"
#include "../utils/utils.h"
#include "../Sound/SoundScreen.h"
#include "../consts.h"

class GameScreen : public Screen
{
private:
    PlayerController player;
    //  Sprite *playerSprite;
    sf::Texture backgroundTexture, enemyTexture;
    EnemySpawner *spawner;
    Clock clock;
    Sprite *background;
   // SoundBuffer buffer;
  //  Sound *sound;
    int map[400] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

public:
    GameScreen()
    {
       // buffer.loadFromFile(getResourcePath() + "test.wav");
        
       // sound = new Sound(buffer);
        
     //   sound->setVolume(GlobalObjects::settings->isMute ? 0.f : 100.f);
      //  sound->play();

        if(!backgroundTexture.loadFromFile(getResourcePath() + "second.jpeg")) {
            std::cout << "Fail to load background" << std::endl;
        }

        for (int i = 0; i < 400; i++)
        {
            if (map[i] == 1)
            {
                for (int j = 1; j < 5; j++)
                {
                    ObjectController::wall((i % 20) * 80 + j * 10, (i / 20) * 80, 1, false, GlobalObjects::objects);
                    ObjectController::wall((i % 20) * 80 + j * 10, (i / 20) * 80 + j * 10, 1, false, GlobalObjects::objects);
                    ObjectController::wall((i % 20) * 80, (i / 20) * 80 + j * 10, 1, true, GlobalObjects::objects);
                }
            }
        };

        background = new Sprite(backgroundTexture);
        background->setScale({1.5, 1.5});
        screenType = 2;
        id = (int)ScreenId::GAME;
        clock.start();
        Texture t(getResourcePath() + "01_idle/idle_1.png");
        //   playerSprite = new Sprite(t);

        // playerSprite->setOrigin({playerSprite->getLocalBounds().size.x / 2, playerSprite->getLocalBounds().size.y / 2});
        //  playerSprite->setPosition({150, 100});

        // TODO
        // Утечка с текстурой, исправить потом для нормального рендера
        if (!enemyTexture.loadFromFile(getResourcePath() + "01_idle/idle_1.png"))
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
        if (GlobalObjects::screenManager->findScreenById((int)ScreenId::MAIN_MENU) != nullptr || GlobalObjects::screenManager->findScreenById((int)ScreenId::CUTSCENE) != nullptr)
        {
            return;
        }
        if (event.is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (event.is<Event::KeyReleased>())
        {
            const auto *keyRealesed = event.getIf<sf::Event::KeyReleased>();
            if (player.getMotion() == 3 || player.getMotion() == 2 || player.getMotion() == 4 || player.getMotion() == 5)
            {
                if (keyRealesed->scancode == Keyboard::Scancode::D && player.velocity.x > 0)
                    player.velocity.x = 0.f;
                if (keyRealesed->scancode == Keyboard::Scancode::A && player.velocity.x < 0)
                    player.velocity.x = 0.f;
                if (keyRealesed->scancode == Keyboard::Scancode::W && player.velocity.y < 0)
                    player.velocity.y = 0.f;
                if (keyRealesed->scancode == Keyboard::Scancode::S && player.velocity.y > 0)
                    player.velocity.y = 0.f;
                if(player.velocity.x > 0)
                {
                    player.setMotion(2);
                }
                else if(player.velocity.x < 0)
                {
                    player.setMotion(3);
                }
                else if(player.velocity.y < 0)
                {
                    player.setMotion(4);
                }
                else if(player.velocity.y > 0)
                {
                    player.setMotion(5);
                }
                //  clock.restart();
                //   player.setMotion(0);
            }
        }
        // key pressed
        else if (event.is<sf::Event::KeyPressed>())
        {

            const auto *keyPressed = event.getIf<sf::Event::KeyPressed>();

            std::cout << (int)keyPressed->scancode << std::endl;

            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
            {
                // Пример тряски при атаке
                GlobalObjects::camera->shake(8.f, 0.15f);
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::E)
            {
                // Пример зума (как при рывке в Hades)
                GlobalObjects::camera->setZoom(1.3f, 0.5f);
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::Q)
            {
                GlobalObjects::camera->setZoom(1.f, 0.5f);
            }

            if (keyPressed->scancode == Keyboard::Scancode::B && player.getMotion() != 1)
            {
                clock.restart();

                player.setMotion(1);
            }

            if (keyPressed->scancode == Keyboard::Scancode::D)
            {
                player.setMotion(2);
            }

            if (keyPressed->scancode == Keyboard::Scancode::A)
            {
                player.setMotion(3);
            }

            if (keyPressed->scancode == Keyboard::Scancode::W)
            {
                player.setMotion(4);
            }

            if (keyPressed->scancode == Keyboard::Scancode::S)
            {
                player.setMotion(5);
            }

          /*  if(keyPressed->scancode == Keyboard::Scancode::M) {
                GlobalObjects::settings->isMute = !GlobalObjects::settings->isMute;
                sound->setVolume(GlobalObjects::settings->isMute ? 0.f : 100.f);
            }*/
            // std::cout << appEvent << std::endl;
        }
    }

    void update(sf::Time deltaTime) override
    {
        if (GlobalObjects::screenManager->findScreenById((int)ScreenId::MAIN_MENU) != nullptr || GlobalObjects::screenManager->findScreenById((int)ScreenId::CUTSCENE) != nullptr)
        {
            return;
        }
        // Обновление логики меню (анимации и т.д.)
        if (GlobalObjects::screenManager->findScreenById(this->id) != nullptr)
        {
            spawner->update(clock.getElapsedTime().asSeconds(), *player.sprite);
        }
    }

    void draw(sf::RenderWindow &window) override
    {
        if (GlobalObjects::screenManager->findScreenById((int)ScreenId::MAIN_MENU) != nullptr)
        {
            return;
        }
        if (GlobalObjects::screenManager->findScreenById(this->id) != nullptr)
        {
            GlobalObjects::camera->update(0.01, player.sprite->getPosition(), player.velocity);
        }
        GlobalObjects::camera->setView(window);
        sf::RectangleShape gridLine;
        gridLine.setFillColor(sf::Color(60, 60, 70, 100));

        for (int i = 0; i <= 40; i++)
        {
            gridLine.setSize({4000.f, 1.f});
            gridLine.setPosition({0.f, i * 100.f});
            window.draw(gridLine);

            gridLine.setSize({1.f, 4000.f});
            gridLine.setPosition({i * 100.f, 0.f});
            window.draw(gridLine);
        }
        window.draw(*background);

        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            window.draw(GlobalObjects::objects[i].drawObject());
        }
        
        spawner->draw(window);

        for (auto &enemy : spawner->getEnemies())
        {
            if (FloatRect(enemy->getPosition(), {enemy->xPadding * 1.f, enemy->yPadding * 1.f}).findIntersection(FloatRect({player.sprite->getPosition().x + player.direction * (player.xPadding / (player.direction > 0 ? 1 : 2)), player.sprite->getPosition().y}, {1.f, player.yPadding / 2.f})))
            {
                // Здесь нужно обрабатывать урон игроку
                // Например: player.takeDamage(enemy->damage);
                if (player.isAttack)
                {
                    enemy->takeDamage(10);
                }
            }
        }

        player.draw(clock, window);

      /*  if (sound->getStatus() == Sound::Status::Stopped)
        {
            sound->play();
        }*/
    }

    void onEnter() override
    {
        std::cout << "Entering main menu" << std::endl;
    }

    void onEntered() override
    {
        GlobalObjects::screenManager->pushScreen(std::make_unique<SoundScreen>());
        std::cout << this->id << std::endl;
        std::cout << "Entered game screen" << std::endl;
    }

    void onExit() override
    {
        GlobalObjects::screenManager->removeScreen((int)ScreenId::SOUND);
        std::cout << "Exiting game screen" << std::endl;
    }

    void handleMenuInput(const sf::Event &event, sf::RenderWindow &window)
    {
    }
    ~GameScreen() override
    {
        std::cout << "DELETE GAME SCREEN" << std::endl;
        delete spawner;
        // delete playerSprite;
        delete background;
       // delete sound;
    }
};