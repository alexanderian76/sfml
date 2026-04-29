#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "PlayerController.h"

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
    fondot.loadFromFile("fondo1.png");

    Sprite fondo(fondot);

    RectangleShape reactange(Vector2f(2, 178));
    reactange.setFillColor(Color(235, 149, 13));
    PlayerController player;
    Clock clock;
    ObjectController obj(500, 600, 200, 200);
    ObjectController obj1(0, 600, 50, 200);
    ObjectController obj2(200, 500, 200, 200);
    obj.check = 1;
    GlobalObjects::objects[0] = obj;
    GlobalObjects::objects = (ObjectController *)realloc(GlobalObjects::objects, sizeof(ObjectController) * 3);
    GlobalObjects::objects[1] = obj1;
    GlobalObjects::objects[2] = obj2;
    GlobalObjects::objectsCount = 3;

    srand(time(NULL));
    appWindow.setFramerateLimit(60);
    appWindow.clear(Color::Black);

    appWindow.draw(fondo);

    for (int i = 0; i < GlobalObjects::objectsCount; i++)
    {
        appWindow.draw(GlobalObjects::objects[i].drawObject());
    }
    clock.start();

    //  appWindow.draw(ff);
    Texture texture;
    texture.loadFromFile("./01_idle/idle_1.png");
    Texture t("./01_idle/idle_1.png");
    Sprite *sprite = new Sprite(t);
    appWindow.draw(*sprite);
    appWindow.display();
    while (appWindow.isOpen())
    {

        appWindow.clear(Color::Black); // 1. ОЧИЩАЕМ экран

        appWindow.draw(fondo); // 2. РИСУЕМ фон

        // 3. РИСУЕМ все объекты
        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            appWindow.draw(GlobalObjects::objects[i].drawObject());
        }

        // std::cout << clock.getElapsedTime().asSeconds() << std::endl;
        int collisionsCount = 0;
        // Texture t("./01_idle/idle_1.png");

   /*     if (player.motion == 0)
        {
            // sprite.setTexture(t);
            if (player.direction == -1)
            {
                sprite->setTextureRect(player.playerRect);
            }
        }
        if (player.motion == 1)
        {
         //   sprite->setTexture(player.texturesAttack1[j % 11]);
            if (player.direction == -1)
            {
                sprite->setTextureRect(player.playerRect);
            }
        }
        if (player.motion == 2)
        {

          //  sprite->setTexture(player.texturesRun[j % 8]);
            player.direction = 1;

            for (int i = 0; i < GlobalObjects::objectsCount; i++)
            {
                if (GlobalObjects::objects[i].checkCollision(*sprite, player.xPadding, player.yPadding, 0))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
                player.moveX(1);
        }
        if (player.motion == 3)
        {
          //  sprite->setTexture(player.texturesRun[j % 8]);
          //  player.direction = -1;
           // player.flipRect(sprite);

          //  sprite->setTextureRect(player.playerRect);

            for (int i = 0; i < GlobalObjects::objectsCount; i++)
            {
                if (GlobalObjects::objects[i].checkCollision(*sprite, player.xPadding, player.yPadding, 0))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
                player.moveX(-1);
        }
        if (player.motion == 4)
        {
          //  sprite->setTexture(player.texturesRun[j % 8]);
            if (player.direction < 0)
            {
                player.flipRect(sprite);

                sprite->setTextureRect(player.playerRect);
            }
            for (int i = 0; i < GlobalObjects::objectsCount; i++)
            {
                if (GlobalObjects::objects[i].checkCollision(*sprite, player.xPadding, player.yPadding, -1))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
                player.moveY(-1);
        }
        if (player.motion == 5)
        {

           // sprite->setTexture(player.texturesRun[j % 8]);
            if (player.direction < 0)
            {
                player.flipRect(sprite);
                sprite->setTextureRect(player.playerRect);
            }
            for (int i = 0; i < GlobalObjects::objectsCount; i++)
            {
                if (GlobalObjects::objects[i].checkCollision(*sprite, player.xPadding, player.yPadding, 1))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
                player.moveY(1);
        }*/
        // cout << "SPrite" << endl;
        player.DrawPlayer(clock, sprite);
        appWindow.draw(*sprite);
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
    return 0;
}