#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "LootSystem.h"
#include "../utils/utils.h"
#include "../Menu/Screen.h"
#include "../Enemy/Enemy.h"
#include "../consts.h"

class LootManager
{
public:
LootManager()
{
    isFontLoaded = font.openFromFile(getResourcePath() + "arialmt.ttf");
    
    // Создаем окно выбора лута
   /* lootWindow = std::make_unique<LootSelectionScreen>();
    lootWindow->setOnItemSelected([this](const LootItem& item) {
        // Применяем эффект выбранного предмета
        std::cout << "Selected item: " << item.name << std::endl;
        // Здесь можно добавить логику применения предмета
        // Например, к игроку или инвентарю
    });*/
    //GlobalObjects::screenManager.pushScreen(std::make_unique<LootSelectionScreen>());
}
    void generateLoot(const sf::Vector2f &position, EnemyType enemyType);
    void update(float deltaTime, const sf::Vector2f &playerPos);
    void draw(sf::RenderWindow &window);

    std::vector<LootDrop> getAvailableLoot() const { return lootDrops; }
    void collectLoot(int index);

    // Добавляем метод для проверки, не открыто ли уже окно
    bool isLootWindowActive() const;
    std::vector<LootDrop> lootDrops;
    std::vector<LootItem> lootItems;
    sf::Vector2f currentPos;

private:

    sf::Font font;
    sf::Texture lootIconTexture;

    //  ScreenManager* screenManager;
    //  std::unique_ptr<LootSelectionScreen> lootWindow;
    bool isFontLoaded;
    int lootWindowId = 1000;

    std::vector<LootItem> generateLootForEnemy(EnemyType type);
    void showLootSelection(const LootDrop &drop);
};