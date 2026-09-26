#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "../Menu/Screen.h"
#include "../GlobalObjects.h"
#include "LootSystem.h"
#include "../consts.h"
#include "../utils/utils.h"
#include <iostream>

class LootSelectionScreen : public Screen
{
public:
    LootSelectionScreen()
    {

        id = (int)ScreenId::LOOT; // Уникальный ID для окна лута
        screenType = 2;           // Тип экрана (2 - UI окно)
        isWindowActive = false;
        // Загружаем шрифт
        isFontLoaded = font.openFromFile(getResourcePath() + "arialmt.ttf");
        if (!isFontLoaded)
        {
            std::cout << "Failed to load font for LootSelectionScreen" << std::endl;
        }
        this->titleText = new sf::Text(font);
        this->controlsText = new sf::Text(font);

        this->selectionArrowText = new sf::Text(font);
        selectionArrowText->setString(">>");
        selectionArrowText->setCharacterSize(20);
        selectionArrowText->setFillColor(sf::Color::Yellow);

        setOnItemSelected([this](const LootItem &item)
                          {
                              // Применяем эффект выбранного предмета
                              std::cout << "Selected item: " << item.name << std::endl;
                              // Здесь можно добавить логику применения предмета
                              // Например, к игроку или инвентарю
                          });
        std::cout << "LootSelectionScreen INITED" << std::endl;
    }

    void show(const sf::Vector2f &position)
    {
        //   std::cout << "LootSelectionScreen SHOW" << std::endl;
        // this->items = items;

        fadeTimer = 0.3f;
        windowPosition = position - sf::Vector2f(150, 100);
        selectedItemIndex = 0; // Выбираем первый предмет по умолчанию
        keyRepeatTimer = 0;
        createUI();
    };

    void close()
    {
        std::cout << "LootSelectionScreen CLOSE" << std::endl;
        isWindowActive = false;
        // Удаляем себя из менеджера экранов
        // Это нужно сделать через ScreenManager
    };

    bool isActive() const { return isWindowActive; }

    void setOnItemSelected(std::function<void(const LootItem &)> callback)
    {
        onItemSelected = callback;
    };

    // Реализация виртуальных методов Screen
    void handleInput(const sf::Event &event, sf::RenderWindow &window) override
    {
        //      std::cout << "LootSelectionScreen INPUT" << std::endl;
        if (!isWindowActive)
            return;

        // Обработка клавиатуры
        if (event.is<sf::Event::KeyPressed>())
        {
            const auto *keyPressed = event.getIf<sf::Event::KeyPressed>();
            switch (keyPressed->scancode)
            {
            case sf::Keyboard::Scancode::Up:
            {
                // Выбор предыдущего предмета
                int newIndex = selectedItemIndex - 1;
                if (newIndex < 0)
                    newIndex = items.size() - 1;
                selectItem(newIndex);
                break;
            }
            case sf::Keyboard::Scancode::Down:
            {
                // Выбор следующего предмета
                int newIndex = selectedItemIndex + 1;
                if (newIndex >= static_cast<int>(items.size()))
                    newIndex = 0;
                selectItem(newIndex);
                break;
            }
            case sf::Keyboard::Scancode::Space:
            case sf::Keyboard::Scancode::Enter:
            {
                // Подтверждение выбора
                confirmSelection();
                break;
            }
            case sf::Keyboard::Scancode::Escape:
            {
                // Закрытие окна
                close();
                break;
            }
            default:
                break;
            }
        }

        // Также оставляем поддержку мыши для удобства
    };
    void update(sf::Time deltaTime) override
    {
        //     std::cout << "LootSelectionScreen UPDATE" << std::endl;
        if (!isWindowActive)
            return;

        if (fadeTimer > 0)
            fadeTimer -= deltaTime.asSeconds();

        // Поддержка удержания клавиш
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
        {
            keyRepeatTimer += deltaTime.asSeconds();

            if (keyRepeatTimer >= keyRepeatDelay)
            {
                keyRepeatTimer = 0;

                // Проверяем, какая клавиша зажата
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
                {
                    int newIndex = selectedItemIndex - 1;
                    if (newIndex < 0)
                        newIndex = items.size() - 1;
                    selectItem(newIndex);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
                {
                    int newIndex = selectedItemIndex + 1;
                    if (newIndex >= static_cast<int>(items.size()))
                        newIndex = 0;
                    selectItem(newIndex);
                }
            }
        }
        else
        {
            keyRepeatTimer = 0;
        }
    };

    void draw(sf::RenderWindow &window) override
    {
        //     std::cout << "LootSelectionScreen DRAW" << std::endl;
        if (!isWindowActive)
            return;

        // Рисуем затемнение фона
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        // Рисуем окно
        window.draw(background);
        window.draw(*titleText);
        window.draw(*controlsText);

        // Рисуем кнопки и текст
        for (size_t i = 0; i < itemButtons.size() && i < itemTexts.size(); i++)
        {
            window.draw(*(itemButtons)[i]);
            window.draw(*(itemTexts)[i]);
        }

        // Добавляем маленькую стрелку у выбранного предмета
        if (selectedItemIndex >= 0 && selectedItemIndex < static_cast<int>(itemButtons.size()))
        {
            selectionArrowText->setPosition((itemButtons)[selectedItemIndex]->getPosition() - sf::Vector2f(20, 5));
            window.draw(*selectionArrowText);
        }
    };
    void onEnter() override
    {
        std::cout << "LootSelectionScreen enter" << std::endl;
        selectedItemIndex = 0;
        keyRepeatTimer = 0;

        this->items.clear();

        std::for_each(GlobalObjects::lootManager->lootItems.begin(), GlobalObjects::lootManager->lootItems.end(), [this](LootItem &s)
                      { this->items.push_back(s); });

        std::cout << "LootSelectionScreen ITEMS " << this->items.size() << std::endl;

        show(GlobalObjects::lootManager->currentPos);
    };
    void onEntered() override
    {
        std::cout << "LootSelectionScreen entered" << std::endl;
    }
    void onExit() override
    {
        std::cout << "LootSelectionScreen exited" << std::endl;
        isWindowActive = false;
        items.clear();
        itemButtons.clear();
        itemTexts.clear();
        selectedItemIndex = 0;
    };
    ~LootSelectionScreen() override
    {
        std::cout << "LootSelectionScreen DELETE" << std::endl;
        delete titleText;
        delete controlsText;
        delete selectionArrowText;
    }

private:
    std::vector<LootItem> items;
    std::vector<sf::RectangleShape *> itemButtons;
    std::vector<sf::Text *> itemTexts;
    sf::RectangleShape background;
    sf::Text *titleText;
    sf::Text *controlsText;
    sf::Text *selectionArrowText;
    sf::Font font;
    float fadeTimer = 0;
    sf::Vector2f windowPosition;
    std::function<void(const LootItem &)> onItemSelected;

    // Для управления с клавиатуры
    int selectedItemIndex = 0;
    float keyRepeatTimer = 0;
    float keyRepeatDelay = 0.2f;

    void createUI()
    {
        //    std::cout << "LootSelectionScreen CREATE UI" << std::endl;

        itemButtons.clear();
        itemTexts.clear();
        std::cout << "CLEAR" << std::endl;
        // Фон окна
        background.setSize(sf::Vector2f(300, 80 + items.size() * 45));
        background.setFillColor(sf::Color(30, 30, 30, 230));
        background.setOutlineThickness(2);
        background.setOutlineColor(sf::Color::White);
        background.setPosition(windowPosition);
        std::cout << "LootSelectionScreen CREATE UI 1" << std::endl;
        // Заголовок
        // titleText->setFont(font);
        titleText->setString("Select an item:");
        titleText->setCharacterSize(18);
        titleText->setFillColor(sf::Color::White);
        titleText->setPosition(windowPosition + sf::Vector2f(20, 15));

        std::cout << "LootSelectionScreen CREATE UI 2" << std::endl;
        // Управление клавишами
        // controlsText->setFont(font);
        controlsText->setString("Arrows to navigate  [SPACE/ENTER] to select  [ESC] to cancel");
        controlsText->setCharacterSize(10);
        controlsText->setFillColor(sf::Color(180, 180, 180));
        controlsText->setPosition(windowPosition + sf::Vector2f(20, 45));

        // Создаем кнопки для каждого предмета
        for (size_t i = 0; i < items.size(); i++)
        {
            sf::RectangleShape *button = new sf::RectangleShape(sf::Vector2f(260, 35));

            // Выделяем выбранный предмет
            if (i == static_cast<size_t>(selectedItemIndex))
            {
                button->setFillColor(sf::Color::White);
            }
            else
            {
                button->setFillColor(items[i].color);
            }

            button->setPosition(windowPosition + sf::Vector2f(20, 70 + i * 40));
            button->setOutlineThickness(1);
            button->setOutlineColor(sf::Color::White);

            sf::Text *text = new sf::Text(font);

            std::string itemText = items[i].name + " - " + items[i].description;
            if (items[i].type == LootType::HEALTH_POTION || items[i].type == LootType::MANA_POTION)
            {
                itemText += " (+" + std::to_string((int)items[i].value) + ")";
            }
            else if (items[i].type == LootType::WEAPON || items[i].type == LootType::ARMOR)
            {
                itemText += " (+" + std::to_string((int)items[i].value) + ")";
            }
            else if (items[i].type == LootType::GOLD)
            {
                itemText += " (" + std::to_string((int)items[i].value) + " coins)";
            }
            else if (items[i].type == LootType::EXPERIENCE)
            {
                itemText += " (+" + std::to_string((int)items[i].value) + " XP)";
            }

            text->setString(itemText);
            text->setCharacterSize(14);

            // Если предмет выбран, текст черный, иначе белый
            if (i == static_cast<size_t>(selectedItemIndex))
            {
                text->setFillColor(sf::Color::Black);
            }
            else
            {
                text->setFillColor(sf::Color::White);
            }

            text->setPosition(button->getPosition() + sf::Vector2f(10, 8));

            itemButtons.push_back(button);
            itemTexts.push_back(text);
        }
    };

    void selectItem(int index)
    {
        if (index < 0 || index >= static_cast<int>(items.size()))
            return;
        selectedItemIndex = index;
        std::cout << "SELECT" << std::endl;
        createUI(); // Пересоздаем UI для обновления выделения
    };

    void confirmSelection()
    {
        if (selectedItemIndex >= 0 && selectedItemIndex < static_cast<int>(items.size()))
        {
            if (onItemSelected)
            {
                onItemSelected(items[selectedItemIndex]);
            }
            close();
        }
    };
    bool isFontLoaded = false;
};