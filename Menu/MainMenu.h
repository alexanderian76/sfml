// MainMenuScreen.hpp
#pragma once
#include "Screen.h"
#include "Menu.h"
#include "GameScreen.h"
#include <iostream>
#include "../consts.h"
#include "../utils/utils.h"

class MainMenuScreen : public Screen {
private:
    Menu menu;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;

public:
    MainMenuScreen() {
        screenType = 1;
        id = (int)ScreenId::MAIN_MENU;
        // Загрузка фона (опционально)
        if (backgroundTexture.loadFromFile(getResourcePath() + "fondo1.png")) {
            background.setSize(sf::Vector2f(GlobalObjects::settings->resolution.x, GlobalObjects::settings->resolution.y));
            background.setTexture(&backgroundTexture);
        } else {
            background.setSize(sf::Vector2f(800, 600));
            background.setFillColor(sf::Color(50, 50, 50));
        }
        
        // Настройка пунктов меню
        menu.addItem("Start Game", []() {
            std::cout << "Starting game..." << std::endl;
            GlobalObjects::screenManager->removeScreen((int)ScreenId::MAIN_MENU);
            GlobalObjects::screenManager->removeScreen((int)ScreenId::GAME);
            GlobalObjects::screenManager->pushScreen(std::make_unique<GameScreen>());

        });
        
        menu.addItem("Settings", []() {
            std::cout << "Opening settings..." << std::endl;
            // Здесь логика настроек
            GlobalObjects::settings->resolution.x = 1000;
            GlobalObjects::settings->resolution.y = 800;
            
        });
        
        menu.addItem("Exit", []() {
            std::cout << "Exiting game..." << std::endl;
            std::exit(0);
        });
      //  std::cout << "HELLO" << std::endl;
        menu.setItemPositions(400, 250, 80);
        menu.setColors(sf::Color::White, sf::Color::Yellow);
       // std::cout << "HELLO" << std::endl;
    }
    
    void handleInput(const sf::Event& event, sf::RenderWindow &window) override {
        menu.handleInput(event);
        // Для обработки input нам нужен доступ к окну,
        // поэтому этот метод может быть расширен
    }
    
    void update(sf::Time deltaTime) override {
        // Обновление логики меню (анимации и т.д.)
    }
    
    void draw(sf::RenderWindow& window) override {
       
        window.draw(background);
        
        menu.draw(window);
    }

     void onEnter() override {
        std::cout << "Entering main menu" << std::endl;
    }
    
    void onExit() override {
        std::cout << "Exiting main menu" << std::endl;
    }
    
    void handleMenuInput(const sf::Event& event, sf::RenderWindow& window) {
        menu.handleInput(event);
    }
};