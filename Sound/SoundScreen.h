#pragma once

#include "../Menu/Screen.h"
#include "../GlobalObjects.h"
#include <SFML/Audio.hpp>
#include "../utils/utils.h"

class SoundScreen : public Screen
{
private:
    Sound *sound;
    SoundBuffer buffer;

public:
    SoundScreen()
    {
        this->id = 4;
        this->screenType = 4;
        std::cout << "HELLO " << GlobalObjects::screenManager->currentScreenId() << std::endl;
        if (GlobalObjects::screenManager->findScreenById(2) != nullptr)
        {

            if(!buffer.loadFromFile(getResourcePath() + "test.wav"))
                std::cout << "Fail to load sound" << std::endl;
            sound = new Sound(buffer);
            sound->setVolume(GlobalObjects::settings->isMute ? 0.f : 100.f);
            sound->play();
        }
    }
    ~SoundScreen() override
    {
        try
        {
            if (sound != nullptr)
                delete sound;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void update(sf::Time deltaTime) override
    {
        try
        {
            if (sound != nullptr && sound->getStatus() == Sound::Status::Stopped)
            {
                sound->play();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void onEnter() override
    {
    }
    void onExit() override
    {
    }

    void handleInput(const sf::Event &event, sf::RenderWindow &window) override
    {
        try
        {
            if (event.is<sf::Event::KeyPressed>())
            {
                const auto *pressedKey = event.getIf<sf::Event::KeyPressed>();
                if (pressedKey->scancode == sf::Keyboard::Scancode::M)
                {
                    GlobalObjects::settings->isMute = !GlobalObjects::settings->isMute;
                    sound->setVolume(GlobalObjects::settings->isMute ? 0.f : 100.f);
                }
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void draw(sf::RenderWindow &window) override
    {
    }
};