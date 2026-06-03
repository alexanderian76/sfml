// MainMenuScreen.hpp
#pragma once
#include "Screen.h"
#include "Menu.h"
#include "GameScreen.h"
#include <iostream>

class MainMenuScreen : public Screen {
private:
    Menu menu;
    sf::RectangleShape background;
    sf::Texture backgroundTexture;

public:
    MainMenuScreen() {
        screenType = 1;
        // Загрузка фона (опционально)
        if (backgroundTexture.loadFromFile("fondo1.png")) {
            background.setSize(sf::Vector2f(800, 600));
            background.setTexture(&backgroundTexture);
        } else {
            background.setSize(sf::Vector2f(800, 600));
            background.setFillColor(sf::Color(50, 50, 50));
        }
        
        // Настройка пунктов меню
        menu.addItem("Start Game", []() {
            std::cout << "Starting game..." << std::endl;
            GlobalObjects::screenManager->popScreen();
            GlobalObjects::screenManager->pushScreen(std::make_unique<GameScreen>());

        });
        
        menu.addItem("Settings", []() {
            std::cout << "Opening settings..." << std::endl;
            // Здесь логика настроек
            GlobalObjects::screenWidth = 1000;
            GlobalObjects::screenHeight = 800;
            
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