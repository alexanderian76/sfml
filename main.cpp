#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "PlayerController.h"
#include "./Enemy/EnemySpawner.h"

#include "GlobalObjects.h"

// g++ main.cpp -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
using namespace sf;

int main()
{
    SoundBuffer buffer;
    buffer.loadFromFile("test.wav");
    Sound sound(buffer);
    sound.setBuffer(buffer);
    sound.setVolume(50);
    sound.play();

    RenderWindow appWindow(VideoMode({1600, 1000}, 8), "Bubble sort");

    int j = 0;
    // Event appEvent;
    Texture fondot;
    fondot.loadFromFile("696.jpg");

    Sprite fondo(fondot);

    RectangleShape reactange(Vector2f(2, 178));
    reactange.setFillColor(Color(235, 149, 13));
    PlayerController player;
    Clock clock;
    ObjectController obj(500, 600);
    ObjectController obj1(0, 600);
    ObjectController obj2(200, 500);
    obj.check = 1;

    GlobalObjects::objects.push_back(obj);
    GlobalObjects::objects.push_back(obj1);
    GlobalObjects::objects.push_back(obj2);

    auto wall = ObjectController::wall(200, 400, 10, false);

    GlobalObjects::objects.insert(GlobalObjects::objects.end(), std::make_move_iterator(wall.begin()), std::make_move_iterator(wall.end()));
    wall.clear();
    srand(time(NULL));
    appWindow.setFramerateLimit(60);
    appWindow.clear(Color::Black);

    appWindow.draw(fondo);

    for (int i = 0; i < GlobalObjects::objects.size(); i++)
    {
        appWindow.draw(GlobalObjects::objects[i].drawObject());
    }
    clock.start();

    //  appWindow.draw(ff);
    Texture texture;
    texture.loadFromFile("./01_idle/idle_1.png");
    Texture t("./01_idle/idle_1.png");
    Sprite *sprite = new Sprite(t);

    sprite->setOrigin({sprite->getLocalBounds().size.x / 2, sprite->getLocalBounds().size.y / 2});
    sprite->setPosition({250, 150});
    // Загрузка текстуры врага (замените на свой файл)
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("./01_idle/idle_1.png"))
    {
        std::cerr << "Failed to load enemy texture!" << std::endl;
        return -1;
    }

    // Создание спавнера врагов
    EnemySpawner spawner(enemyTexture);
    spawner.setSpawnRate(1.5f); // Спавн каждые 1.5 секунды
    spawner.setMaxEnemies(15);

    appWindow.draw(*sprite);
    appWindow.display();
    while (appWindow.isOpen())
    {

        appWindow.clear(Color::Black); // 1. ОЧИЩАЕМ экран

        appWindow.draw(fondo); // 2. РИСУЕМ фон

        // 3. РИСУЕМ все объекты
        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            appWindow.draw(GlobalObjects::objects[i].drawObject());
        }

        // Обновление спавнера
        spawner.update(clock.getElapsedTime().asSeconds(), *sprite);

        spawner.draw(appWindow);

        // Проверка коллизий с игроком
        for (auto &enemy : spawner.getEnemies())
        {
            if (FloatRect(enemy->getPosition(), {enemy->xPadding, enemy->yPadding}).findIntersection(FloatRect({sprite->getPosition().x + player.direction * (player.xPadding / (player.direction > 0 ? 1 : 2)), sprite->getPosition().y}, {1, player.yPadding / 2})))
            {
                // Здесь нужно обрабатывать урон игроку
                // Например: player.takeDamage(enemy->damage);
                if (player.isAttack)
                {
                    enemy->takeDamage(10);
                }
            }
        }
      //  cout << "WALL" << endl;
      //  cout << wall.size() << endl;
        int collisionsCount = 0;

        player.DrawPlayer(clock, sprite, appWindow);

        appWindow.display();

        if (sound.getStatus() == Sound::Status::Stopped)
        {
            sound.play();
        }
        while (const std::optional appEvent = appWindow.pollEvent())
        {

            if (appEvent->is<Event::Closed>())
                appWindow.close();

            // window closed
            if (appEvent->is<sf::Event::Closed>())
            {
                appWindow.close();
            }
            else if (appEvent->is<Event::KeyReleased>())
            {
                if (player.getMotion() == 3 || player.getMotion() == 2 || player.getMotion() == 4 || player.getMotion() == 5)
                {
                    clock.restart();
                    player.setMotion(0);
                }
            }
            // key pressed
            else if (appEvent->is<sf::Event::KeyPressed>())
            {

                const auto *keyPressed = appEvent->getIf<sf::Event::KeyPressed>();

                //  std::cout << (keyPressed->scancode == Keyboard::Scancode::A) << std::endl;

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
            // we don't process other types of events
        }
    }

    ////////////////////////////////////////////// ////////////////////////////////////////////// //////////////////////////////////////////////
    delete sprite;

    
    GlobalObjects::objects.clear();
    return 0;
}