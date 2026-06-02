// MenuItem.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <memory>
#include <iostream>

class MenuItem {
private:
    sf::Text text;
    sf::RectangleShape background;
    bool isSelected;
    std::function<void()> callback;
    sf::Color normalColor;
    sf::Color selectedColor;
    
public:
    MenuItem(const std::string& textStr, const sf::Font& font, 
             unsigned int fontSize, sf::Color normalCol, 
             sf::Color selectedCol)
        : text(font, textStr, fontSize),  // SFML 3: конструктор требует font и строку
          isSelected(false),
          normalColor(normalCol),
          selectedColor(selectedCol) {
        
        text.setFillColor(normalColor);
        
        // Настройка фона
        sf::FloatRect textBounds = text.getLocalBounds();
        
        background.setSize(sf::Vector2f(textBounds.size.x + 40.f, 
                                        textBounds.size.y + 20.f));
        background.setFillColor(sf::Color::Transparent);
        background.setOutlineThickness(2);
        background.setOutlineColor(sf::Color::Transparent);
  //      std::cout << "HELLO" << std::endl;
        callback = nullptr;
    }
    
    void setPosition(float x, float y) {
        sf::FloatRect textBounds = text.getLocalBounds();
        background.setPosition({x - textBounds.size.x / 2 - 20, y});
        // SFML 3: setPosition принимает sf::Vector2f или два float
        text.setPosition({x - textBounds.size.x / 2, y});
    }
    
    void select(bool selected) {
        isSelected = selected;
        if (selected) {
            text.setFillColor(selectedColor);
            background.setOutlineColor(selectedColor);
            background.setFillColor(sf::Color(selectedColor.r, 
                                              selectedColor.g, 
                                              selectedColor.b, 50));
        } else {
            text.setFillColor(normalColor);
            background.setOutlineColor(sf::Color::Transparent);
            background.setFillColor(sf::Color::Transparent);
        }
    }
    
    void setCallback(std::function<void()> func) {
        callback = func;
    }
    
    void execute() const {
        if (callback) {
            callback();
        }
    }
    
    bool contains(sf::Vector2f point) const {
        return background.getGlobalBounds().contains(point);
    }
    
    void draw(sf::RenderWindow& window) const {
        // std::cout << "HELLO ITEM" << std::endl;
        
        window.draw(background);
        window.draw(text);
         
    }
};