// Screen.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <iostream>

// Базовый класс для всех экранов (меню, игра, настройки)
class Screen {
public:
    virtual ~Screen() = default;
    virtual void handleInput(const sf::Event& event, sf::RenderWindow &window) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
    int screenType = 0;
};

// Менеджер экранов
class ScreenManager {
private:
    std::stack<std::unique_ptr<Screen>> screens;
    
public:
    void pushScreen(std::unique_ptr<Screen> screen) {
        std::cout << "PUSH_SCREEN" << std::endl;
        if (!screens.empty()) {
            screens.top()->onExit();
        }
       
        screen->onEnter();
        screens.push(std::move(screen));
    }

    int currentScreenType() {
        if(!screens.empty())
            return screens.top()->screenType;
    }
    
    void popScreen() {
        if (!screens.empty()) {
            screens.top()->onExit();
            screens.pop();
        }
        if (!screens.empty()) {
            screens.top()->onEnter();
        }
    }
    
    void handleInput(const sf::Event& event, sf::RenderWindow &window) {
        if (!screens.empty()) {
            screens.top()->handleInput(event, window);
        }
    }
    
    void update(sf::Time deltaTime) {
        if (!screens.empty()) {
            screens.top()->update(deltaTime);
        }
    }
    
    void draw(sf::RenderWindow& window) {
        if (!screens.empty()) {
            
            screens.top()->draw(window);
        }
    }
    
    bool isEmpty() const {
        return screens.empty();
    }

};