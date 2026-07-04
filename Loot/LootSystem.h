#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>

enum class LootType
{
    WEAPON,
    ARMOR,
    HEALTH_POTION,
    MANA_POTION,
    GOLD,
    EXPERIENCE
};

struct LootItem
{
    LootType type;
    std::string name;
    std::string description;
    float value; // Урон для оружия, защита для брони, количество для зелий
    sf::Color color;
    //sf::Texture icon;
    
    LootItem(LootType t, const std::string& n, const std::string& desc, float val, sf::Color col = sf::Color::White)
        : type(t), name(n), description(desc), value(val), color(col) {}
};

struct LootDrop
{
    std::vector<LootItem> items;
    sf::Vector2f position;
    float timer; // Время до исчезновения
    bool isCollected;
    
    LootDrop(const sf::Vector2f& pos) : position(pos), timer(10.0f), isCollected(false) {}
};