#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdio.h>

enum class EnemyType
{
    BASIC,
    FAST,
    TANK,
    RANGED
};

class Enemy
{
public:
    Enemy(EnemyType type, sf::Vector2f startPos, sf::Texture &texture);

    void update(float deltaTime, const sf::Sprite &playerSprite);
    void draw(sf::RenderWindow &window);
    void takeDamage(float damage);
    bool isAlive() const { return health > 0; }

    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    EnemyType getType() const { return type; }
    float getHealth() const { return health; }

    float getMaxHealth() const;

    bool checkCollision(sf::Sprite &sprite);

    void setColor(const sf::Color &color);
    static const int xPadding = 90;
    static const int yPadding = 60;
    int damageTimer = 0;

    ~Enemy()
    {
        std::cout << "DELETE Enemy" << std::endl;
        delete sprite;
        delete[] texturesRun;

        texturesRun = nullptr;
        health = NULL;
        speed = NULL;
        damage = NULL;
        attackCooldown = NULL;
        attackTimer = NULL;
        isAttack = NULL;
    }

private:
    EnemyType type;
    sf::Sprite *sprite;
    float health;
    float speed;
    float damage;
    float attackCooldown;
    float attackTimer;
    bool isAttack;
    sf::Texture *texturesRun;

    void initStats();
    sf::Color getColorForType();
};
