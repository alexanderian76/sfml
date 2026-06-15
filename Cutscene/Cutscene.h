#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../Menu/Screen.h"
#include "../GlobalObjects.h"

#include "../utils/utils.h"

struct DialogueLine
{
    std::string speaker;
    std::string text;
    float duration; // длительность показа в секундах
};

class Cutscene : public Screen
{
private:
    sf::Text speakerText;
    sf::Text dialogueText;
    sf::RectangleShape dialogueBox;
    sf::RectangleShape nameBox;

    std::vector<DialogueLine> lines;
    size_t currentLine = 0;
    sf::Clock lineTimer;
    bool cutsceneActive = true;

    // Для плавного появления текста
    std::string displayedText;
    size_t textIndex = 0;
    sf::Clock textAnimationTimer;
    const float TEXT_ANIMATION_DELAY = 0.03f;

public:
    Cutscene(const std::string &textStr, const sf::Font &font,
             unsigned int fontSize)
        : speakerText(font, textStr, fontSize),
          dialogueText(font, textStr, fontSize)
    {
        screenType = 3;
        id = 3;
        textAnimationTimer.start();
        // Настройка фонового изображения для диалогового окна
        dialogueBox.setSize(sf::Vector2f(800, 150));
        dialogueBox.setPosition(sf::Vector2f(GlobalObjects::camera->getScreenPosition().x / 2 + 50, GlobalObjects::camera->getScreenPosition().y / 2 + 550));
        dialogueBox.setFillColor(sf::Color(0, 0, 0, 220));
        dialogueBox.setOutlineColor(sf::Color::White);
        dialogueBox.setOutlineThickness(2);

        // Настройка окна с именем персонажа
        nameBox.setSize(sf::Vector2f(200, 40));
        nameBox.setPosition(sf::Vector2f(GlobalObjects::camera->getScreenPosition().x / 2 + 50, GlobalObjects::camera->getScreenPosition().y / 2 + 510));
        nameBox.setFillColor(sf::Color(50, 50, 50, 220));
        nameBox.setOutlineColor(sf::Color::White);
        nameBox.setOutlineThickness(1);

        // Настройка текста
        speakerText.setFont(font);
        speakerText.setCharacterSize(24);
        speakerText.setFillColor(sf::Color::Yellow);
        speakerText.setPosition(sf::Vector2f(GlobalObjects::camera->getScreenPosition().x / 2 + 60, GlobalObjects::camera->getScreenPosition().y / 2 + 515));

        dialogueText.setFont(font);
        dialogueText.setCharacterSize(20);
        dialogueText.setFillColor(sf::Color::White);
        dialogueText.setPosition(sf::Vector2f( GlobalObjects::camera->getScreenPosition().x / 2 + 60, GlobalObjects::camera->getScreenPosition().y / 2 + 565));

        // Создание фона катсцены
        sf::RectangleShape background(sf::Vector2f(1024, 768));
        background.setFillColor(sf::Color(20, 20, 40));

        // Добавление декоративного элемента
        sf::CircleShape ornament(100);
        ornament.setPosition(sf::Vector2f(GlobalObjects::camera->getScreenPosition().x / 2 + 700, GlobalObjects::camera->getScreenPosition().y / 2 + 200));
        ornament.setFillColor(sf::Color(100, 100, 200, 100));

        sf::RectangleShape ground(sf::Vector2f(1024, 100));
        ground.setPosition(sf::Vector2f(GlobalObjects::camera->getScreenPosition().x / 2, GlobalObjects::camera->getScreenPosition().y / 2 + 668));
        ground.setFillColor(sf::Color(40, 40, 60));

        // Добавление диалоговых строк
        addDialogueLine("Герой", "Похоже, я наконец-то добрался до замка...", 4.0f);
        addDialogueLine("Герой", "Столько лет поисков не прошли даром!", 3.5f);
        addDialogueLine("Таинственный голос", "Ты пришёл... Я ждал тебя, избранный.", 4.0f);
        addDialogueLine("Герой", "Кто ты? Покажись!", 2.5f);
        addDialogueLine("Таинственный голос", "Всему своё время. Сначала докажи, что достоин.", 4.5f);
        addDialogueLine("Герой", "Я готов к любым испытаниям!", 3.0f);
        addDialogueLine("Таинственный голос", "Тогда вперёд. Судьба ждёт!", 3.0f);
    }

    void addDialogueLine(const std::string &speaker, const std::string &text, float duration = 3.0f)
    {
        lines.push_back({speaker, text, duration});
    }

    void update(sf::Time deltaTime) override
    {
        if (!cutsceneActive)
            return;

        // Анимация появления текста
        if (textIndex < lines[currentLine].text.length())
        {
            if (textAnimationTimer.getElapsedTime().asSeconds() >= TEXT_ANIMATION_DELAY)
            {
                displayedText += lines[currentLine].text[textIndex];
                textIndex++;
                textAnimationTimer.restart();
            }
        }

        // Переключение на следующую строку по времени
        if (lineTimer.getElapsedTime().asSeconds() >= lines[currentLine].duration)
        {
            nextDialogueLine();
        }
    }

    void nextDialogueLine()
    {
        currentLine++;
        if (currentLine >= lines.size())
        {
            cutsceneActive = false;
        }
        else
        {
            // Сброс для новой строки
            displayedText.clear();
            textIndex = 0;
            lineTimer.restart();
            textAnimationTimer.restart();
        }
    }

    void handleInput(const sf::Event &event, sf::RenderWindow &window) override
    {
        if (event.is<sf::Event::KeyPressed>())
        {

            const auto *keyPressed = event.getIf<sf::Event::KeyPressed>();

            std::cout << (int)keyPressed->scancode << std::endl;

            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
            {
                GlobalObjects::screenManager->removeScreen(3);
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::X)
            {
                if (currentLine < lines.size() && textIndex < lines[currentLine].text.length())
                {
                    textIndex = lines[currentLine].text.length();
                    displayedText = lines[currentLine].text;
                }
                else
                {
                    nextDialogueLine();
                }
            }
        }
    }

    void draw(sf::RenderWindow &window) override
    {
        if (!cutsceneActive)
            return;

        // Обновление отображаемого текста
        speakerText.setString(toSFString(lines[currentLine].speaker));
        dialogueText.setString(toSFString(displayedText));

        window.draw(dialogueBox);
        window.draw(nameBox);
        window.draw(speakerText);
        window.draw(dialogueText);
    }

    bool isActive() const
    {
        return cutsceneActive;
    }

    void onEnter() override
    {
        std::cout << "Entering main menu" << std::endl;
    }

    void onExit() override
    {
        std::cout << "Exiting main menu" << std::endl;
    }
};
