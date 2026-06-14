// Screen.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <iostream>
#include <vector>

// Базовый класс для всех экранов (меню, игра, настройки)
class Screen
{
public:
    virtual ~Screen() = default;
    virtual void handleInput(const sf::Event &event, sf::RenderWindow &window) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
    int screenType = 0;
    int id = 0;
};

// Менеджер экранов
class ScreenManager
{
private:
    std::vector<std::unique_ptr<Screen>> screens;

public:
    void pushScreen(std::unique_ptr<Screen> screen)
    {
        std::cout << "PUSH_SCREEN" << std::endl;
        int id = screen->id;
        if (!screens.empty())
        {
            screens.back()->onExit();

            // screens.top()->onExit();
        }

        screen->onEnter();
        screens.push_back(std::move(screen));
    }

    int currentScreenType()
    {
        if (!screens.empty())
            return screens.back()->screenType;
    }

    int currentScreenId()
    {
        if (!screens.empty())
            return screens.back()->id;
    }

    void removeScreen(int id)
    {
        if (!screens.empty())
        {
            // screens.at(0)->onExit();
            auto tmpScreen = std::find_if(screens.begin(), screens.end(), [id](std::unique_ptr<Screen> &s)
                                          { return s->id == id; });
            if (tmpScreen->get())
            {
                tmpScreen->get()->onExit();
                std::erase_if(screens, [id](std::unique_ptr<Screen> &s)
                              { return s->id == id; });
            }
        }
        if (!screens.empty())
        {
            screens.back()->onEnter();
        }
    }

    void handleInput(const sf::Event &event, sf::RenderWindow &window)
    {
        if (!screens.empty())
        {
            screens.back()->handleInput(event, window);
        }
    }

    void update(sf::Time deltaTime)
    {
        if (!screens.empty())
        {
            std::for_each(screens.begin(), screens.end(), [&deltaTime](std::unique_ptr<Screen>& s) {
                s->update(deltaTime);
            });
            //screens.back()->update(deltaTime);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        if (!screens.empty())
        {
            std::for_each(screens.begin(), screens.end(), [&window](std::unique_ptr<Screen>& s) {
                s->draw(window);
            });
          //  screens.back()->draw(window);
        }
    }

    bool isEmpty() const
    {
        return screens.empty();
    }
};