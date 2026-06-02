// Menu.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include "MenuItem.h"
#include <iostream>

class Menu {
private:
    std::vector<MenuItem> items;
    int selectedIndex;
    sf::Font font;
    bool visible;
    sf::Color normalColor;
    sf::Color selectedColor;
    
public:
    Menu() : selectedIndex(-1), visible(true),
             normalColor(sf::Color::White),
             selectedColor(sf::Color::Yellow), font() {
        // Пытаемся загрузить шрифт
        
        if (!font.openFromFile("arialmt.ttf")) {
            // В случае ошибки можно использовать встроенный шрифт
            // или продолжить без него (текст не будет отображаться)
            throw std::runtime_error("Failed to load font");
        }
    }
    
    void addItem(const std::string& text, std::function<void()> callback) {
        
        MenuItem item(text, font, 36, normalColor, selectedColor);
     //   std::cout << "HELLO" << std::endl;
        item.setCallback(callback);
        items.push_back(item);
        
        if (selectedIndex == -1) {
            selectedIndex = 0;
            items[0].select(true);
        }
    }
    
    void setItemPositions(float startX, float startY, float spacing) {
        float y = startY;
        for (auto& item : items) {
            item.setPosition(startX, y);
            y += spacing;
        }
    }
    
    void handleInput(const sf::Event& event) {
        if (!visible) return;
        
        // SFML 3: используем std::visit или is<> для определения типа события
        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
            std::cout << (int)(keyPressed->code) << std::endl;
            switch (keyPressed->code) {
                case sf::Keyboard::Key::Up:
                    if (selectedIndex > 0) {
                        items[selectedIndex].select(false);
                        selectedIndex--;
                        items[selectedIndex].select(true);
                    }
                    break;
                    
                case sf::Keyboard::Key::Down:
                    if (selectedIndex < static_cast<int>(items.size()) - 1) {
                        items[selectedIndex].select(false);
                        selectedIndex++;
                        items[selectedIndex].select(true);
                    }
                    break;
                    
                case sf::Keyboard::Key::Enter:
                    if (selectedIndex >= 0 && 
                        selectedIndex < static_cast<int>(items.size())) {
                        items[selectedIndex].execute();
                    }
                    break;
                    
                default:
                    break;
            }
        }
        else if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
            sf::Vector2f mousePos(static_cast<float>(mouseMoved->position.x),
                                  static_cast<float>(mouseMoved->position.y));
            
            for (size_t i = 0; i < items.size(); ++i) {
                if (items[i].contains(mousePos)) {
                    if (selectedIndex != static_cast<int>(i)) {
                        if (selectedIndex >= 0) {
                            items[selectedIndex].select(false);
                        }
                        selectedIndex = static_cast<int>(i);
                        items[selectedIndex].select(true);
                    }
                    break;
                }
            }
        }
        else if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos(static_cast<float>(mousePressed->position.x),
                                      static_cast<float>(mousePressed->position.y));
                for (auto& item : items) {
                    if (item.contains(mousePos)) {
                        item.execute();
                        break;
                    }
                }
            }
        }
    }
    
    void draw(sf::RenderWindow& window) const {
        if (!visible) return;
        for (const auto& item : items) {
            item.draw(window);
        }
    }
    
    void setVisible(bool isVisible) {
        visible = isVisible;
    }
    
    bool isVisible() const {
        return visible;
    }
    
    void setColors(sf::Color normal, sf::Color selected) {
        normalColor = normal;
        selectedColor = selected;
        // Обновляем существующие элементы
        for (size_t i = 0; i < items.size(); ++i) {
            items[i].select(i == static_cast<size_t>(selectedIndex));
        }
    }
};