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
    Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(50);
    sound.play();
    
    RenderWindow appWindow(VideoMode(1600, 1000, 8), "Bubble sort");
    
    int j = 0;
    Event appEvent;
    Texture fondot;
    fondot.loadFromFile("fondo1.png");

    Sprite fondo(fondot);

    RectangleShape reactange(Vector2f(2, 178));
    reactange.setFillColor(Color(235, 149, 13));
    PlayerController* player = new PlayerController;
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
    while (appWindow.isOpen())
    {
        if(sound.getStatus() == Sound::Status::Stopped)
        {
            sound.play();
        }
        while (appWindow.pollEvent(appEvent))
        {
            if (appEvent.type == Event::Closed)
                appWindow.close();
            switch (appEvent.type)
            {
            // window closed
            case sf::Event::Closed:
                appWindow.close();
                break;
            case Event::KeyReleased:
                if(player->getMotion() == 3 || player->getMotion() == 2 || player->getMotion() == 4 || player->getMotion() == 5)
                {
                    clock.restart();
                    player->setMotion(0);
                    
                }
                break;
            // key pressed
            case sf::Event::KeyPressed:
                if(appEvent.key.code == 0)
                {
                  //  player.setMotion(0);
                    
                }
                if(appEvent.key.code == 1 && player->getMotion() != 1)
                {
                    clock.restart();
                    player->setMotion(1);
                    
                }
                
                if(appEvent.key.code == 3 && player->getMotion() != 2)
                {
                    player->setMotion(2);
                }
                
                if(appEvent.key.code == 0 && player->getMotion() != 3)
                {
                    player->setMotion(3);
                }

                if(appEvent.key.code == 22 && player->getMotion() != 4)
                {
                    player->setMotion(4);
                }

                if(appEvent.key.code == 18 && player->getMotion() != 5)
                {
                    player->setMotion(5);
                }
             //  std::cout << appEvent.key.code << std::endl;
                break;
            // we don't process other types of events
            default:
                break;
            }
        }

        ////////////////////////////////////////////// ////////////////////////////////////////////// //////////////////////////////////////////////
        
        
        appWindow.clear(Color::Black);

        appWindow.draw(fondo);
        
        for(int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            appWindow.draw(GlobalObjects::objects[i].drawObject());
        }
        appWindow.draw(player->DrawPlayer(clock));
        appWindow.display(); 
    }

    return 0;
}