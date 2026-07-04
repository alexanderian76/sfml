#include "LootManager.h"
#include "../utils/utils.h"
#include <random>
#include <iostream>
#include "../GlobalObjects.h"
#include "LootSelectionScreen.h"
#include "../consts.h"

void LootManager::generateLoot(const sf::Vector2f &position, EnemyType enemyType)
{
    // Создаем выпадающий лут
    LootDrop drop(position);
    currentPos = position;
    drop.items = generateLootForEnemy(enemyType);
    lootItems = generateLootForEnemy(enemyType);
    if (!drop.items.empty())
    {
        lootDrops.push_back(drop);
        std::cout << "Loot generated at position (" << position.x << ", " << position.y << ")" << std::endl;
    }
    // GlobalObjects::screenManager->toggleScreenVisibility((int)ScreenId::LOOT);
    if (!lootItems.empty())
    {
        GlobalObjects::screenManager->findScreenById((int)ScreenId::LOOT)->onEnter();
        GlobalObjects::screenManager->findScreenById((int)ScreenId::LOOT)->isWindowActive = true;
    }
}

std::vector<LootItem> LootManager::generateLootForEnemy(EnemyType type)
{
    std::vector<LootItem> items;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    int roll = dis(gen);

    switch (type)
    {
    case EnemyType::BASIC:
        if (roll < 30) // 30% шанс выпадения
        {
            items.push_back(LootItem(LootType::HEALTH_POTION, "Health Potion", "Restores 50 HP", 50, sf::Color::Green));
        }
        if (roll < 50)
        {
            items.push_back(LootItem(LootType::GOLD, "Gold", "10 gold coins", 10, sf::Color::Yellow));
        }
        break;

    case EnemyType::FAST:
        if (roll < 40)
        {
            items.push_back(LootItem(LootType::MANA_POTION, "Mana Potion", "Restores 30 MP", 30, sf::Color::Blue));
        }
        if (roll < 60)
        {
            items.push_back(LootItem(LootType::WEAPON, "Quick Dagger", "Speed +5", 5, sf::Color::Cyan));
        }
        break;

    case EnemyType::TANK:
        if (roll < 50)
        {
            items.push_back(LootItem(LootType::ARMOR, "Heavy Shield", "Defense +10", 10, sf::Color(139, 69, 19)));
        }
        if (roll < 70)
        {
            items.push_back(LootItem(LootType::HEALTH_POTION, "Large Health Potion", "Restores 150 HP", 150, sf::Color::Green));
        }
        break;

    case EnemyType::RANGED:
        if (roll < 35)
        {
            items.push_back(LootItem(LootType::WEAPON, "Crossbow", "Damage +8", 8, sf::Color(255, 140, 0)));
        }
        if (roll < 55)
        {
            items.push_back(LootItem(LootType::EXPERIENCE, "Experience", "+50 XP", 50, sf::Color(255, 215, 0)));
        }
        break;
    }

    // Базовый шанс на любой предмет
    if (items.empty() && dis(gen) < 20)
    {
        items.push_back(LootItem(LootType::GOLD, "Gold", "5 gold coins", 5, sf::Color::Yellow));
    }

    return items;
}

void LootManager::update(float deltaTime, const sf::Vector2f &playerPos)
{
    // Обновляем окно выбора, если оно активно
    if (GlobalObjects::screenManager->findScreenById((int)ScreenId::LOOT) == nullptr)
    {
        // Окно обновляется через ScreenManager
        return;
    }

    for (auto &drop : lootDrops)
    {
        if (drop.isCollected)
            continue;

        drop.timer -= deltaTime;

        // Проверяем, не подобрал ли игрок лут
        float distance = std::sqrt(
            std::pow(drop.position.x - playerPos.x, 2) +
            std::pow(drop.position.y - playerPos.y, 2));

        if (distance < 80.0f && !drop.items.empty())
        {
            // Показываем окно выбора
            showLootSelection(drop);
            return;
        }
    }

    // Удаляем старые дропы
    lootDrops.erase(
        std::remove_if(lootDrops.begin(), lootDrops.end(),
                       [](const LootDrop &drop)
                       { return drop.timer <= 0 || drop.isCollected; }),
        lootDrops.end());
}

void LootManager::showLootSelection(const LootDrop &drop)
{

    // Проверяем, не открыто ли уже окно
    if (GlobalObjects::screenManager->findScreenById((int)ScreenId::LOOT) != nullptr)
    {
        return;
    }

    // Добавляем окно в ScreenManager
    //   GlobalObjects::screenManager.pushScreen(std::make_unique<LootSelectionScreen>());

    // Отмечаем дроп как собранный
    const_cast<LootDrop &>(drop).isCollected = true;
}

void LootManager::draw(sf::RenderWindow &window)
{
    // Рисуем индикаторы лута на земле
    for (const auto &drop : lootDrops)
    {
        if (drop.isCollected)
            continue;

        // Рисуем иконку лута на земле
        sf::CircleShape lootIndicator(8);
        lootIndicator.setFillColor(sf::Color::Yellow);
        lootIndicator.setPosition(drop.position - sf::Vector2f(8, 8));
        window.draw(lootIndicator);

        // Рисуем количество предметов
        if (isFontLoaded)
        {
            sf::Text countText(font);

            countText.setString(std::to_string(drop.items.size()));
            countText.setCharacterSize(12);
            countText.setFillColor(sf::Color::White);
            countText.setPosition(drop.position + sf::Vector2f(12, -10));
            window.draw(countText);

            // Добавляем анимацию парения
            float floatOffset = std::sin(drop.timer * 3.0f) * 3.0f;
            sf::CircleShape glow(12);
            glow.setFillColor(sf::Color(255, 255, 0, 50));
            glow.setPosition(drop.position - sf::Vector2f(12, 12 + floatOffset));
            window.draw(glow);
        }
    }
}

bool LootManager::isLootWindowActive() const
{
    return GlobalObjects::screenManager->findScreenById((int)ScreenId::LOOT) != nullptr;
}

void LootManager::collectLoot(int index)
{
    if (index >= 0 && index < lootDrops.size() && !lootDrops[index].isCollected)
    {
        lootDrops[index].isCollected = true;
        // Применяем эффекты предметов к игроку
        for (const auto &item : lootDrops[index].items)
        {
            switch (item.type)
            {
            case LootType::HEALTH_POTION:
                // health += item.value;
                break;
            case LootType::WEAPON:
                // damage += item.value;
                break;
            case LootType::GOLD:
                // gold += item.value;
                break;
            case LootType::ARMOR:
                // armor += item.value;
                break;
            case LootType::MANA_POTION:
                // mana += item.value;
                break;
            case LootType::EXPERIENCE:
                // exp += item.value;
                break;
            }
        }
    }
}