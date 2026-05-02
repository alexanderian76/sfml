#include "Enemy.h"
#include <iostream>
#include "../GlobalObjects.h"

Enemy::Enemy(EnemyType type, sf::Vector2f startPos, sf::Texture &texture)
    : type(type), health(100), speed(100), damage(25), attackCooldown(1.0f), attackTimer(0)
{
    texturesRun = new Texture[8];
    for (int i = 0; i < 8; i++)
    {
        texturesRun[i].loadFromFile("./02_run/run_" + to_string(i + 1) + ".png");
    }
    sprite = new sf::Sprite(texture);
    sprite->setTexture(texture);
    sprite->setPosition(startPos);
    sprite->setOrigin({sprite->getLocalBounds().size.x / 2, sprite->getLocalBounds().size.y / 2});
    initStats();
    sprite->setColor(getColorForType());
}

void Enemy::initStats()
{
    switch (type)
    {
    case EnemyType::BASIC:
        health = 100;
        speed = 150;
        damage = 25;
        attackCooldown = 1.0f;
        break;
    case EnemyType::FAST:
        health = 50;
        speed = 300;
        damage = 15;
        attackCooldown = 0.5f;
        break;
    case EnemyType::TANK:
        health = 300;
        speed = 80;
        damage = 40;
        attackCooldown = 1.5f;
        break;
    case EnemyType::RANGED:
        health = 80;
        speed = 120;
        damage = 20;
        attackCooldown = 1.2f;
        break;
    }
}

sf::Color Enemy::getColorForType()
{
    switch (type)
    {
    case EnemyType::BASIC:
        return sf::Color::Red;
    case EnemyType::FAST:
        return sf::Color::Yellow;
    case EnemyType::TANK:
        return sf::Color(139, 0, 0); // Dark red
    case EnemyType::RANGED:
        return sf::Color(255, 100, 100);
    default:
        return sf::Color::White;
    }
}

void Enemy::update(float deltaTime, const sf::Sprite &playerSprite)
{
    int j = deltaTime / 0.07f;
    if (attackTimer > 0)
        attackTimer -= deltaTime;

    if (damageTimer == 0)
        sprite->setColor(getColorForType());
    else
        damageTimer--;

    Texture texture;
    texture = texturesRun[j % 8];
    sprite->setTexture(texturesRun[j % 8]);
    // direction = 1;
    // flipRect(sprite);

    // Движение к игроку
    sf::Vector2f direction = playerSprite.getPosition() - sprite->getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 0 && !FloatRect(sprite->getPosition(), {xPadding, yPadding}).findIntersection(FloatRect(playerSprite.getPosition(), {xPadding, yPadding})))
    {

        int collisionsCountX = 0, collisionsCountY = 0;
        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0, direction.x / abs(direction.x)))
                collisionsCountX++;
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, direction.y / abs(direction.y), 0))
                collisionsCountY++;
        }

        if (abs(direction.x) >= abs(direction.y) && collisionsCountX == 0)
        {
            direction.x = direction.x / abs(direction.x);
            direction.y = 0;
        }
        else if (abs(direction.x) <= abs(direction.y) && collisionsCountY == 0)
        {
            direction.y = direction.y / abs(direction.y);
            direction.x = 0;
        }
        else if (abs(direction.x) <= abs(direction.y) && collisionsCountX == 0)
        {
            direction.x = direction.x / abs(direction.x);
            direction.y = 0;
        }
        else if (abs(direction.x) >= abs(direction.y) && collisionsCountY == 0)
        {
            direction.y = direction.y / abs(direction.y);
            direction.x = 0;
        }

        else
        {
            direction.x = 0;
            direction.y = 0;
        }
        if (direction.x != 0 || direction.y != 0)
            sprite->move(direction);
    }
    else if (sprite->getPosition().y != playerSprite.getPosition().y)
    {
        sf::Vector2f directionY = {0, playerSprite.getPosition().y - sprite->getPosition().y};
        int collisionsCount = 0;
        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, directionY.y / abs(directionY.y), 0))
                collisionsCount++;
        }
        if (collisionsCount == 0) {
            directionY.y = directionY.y / abs(directionY.y);
            sprite->move(directionY);
        }
    }

    // float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;
    // sprite->setRotation(sf::degrees(angle + 90.f)); // Используем sf::degrees(
}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);

    // Отрисовка полоски здоровья
    sf::RectangleShape healthBar(sf::Vector2f(40, 5));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition({sprite->getPosition().x - 20, sprite->getPosition().y - 30});
    window.draw(healthBar);

    sf::RectangleShape currentHealth(sf::Vector2f(40 * (health / getMaxHealth()), 5));
    currentHealth.setFillColor(sf::Color::Green);
    currentHealth.setPosition({sprite->getPosition().x - 20, sprite->getPosition().y - 30});
    window.draw(currentHealth);
}

void Enemy::takeDamage(float damage)
{
    health -= damage;
    if (health < 0)
        health = 0;

    // Эффект получения урона - мигание
    damageTimer = 6;
    sprite->setColor(sf::Color::Blue);
}

bool Enemy::checkCollision(sf::Sprite &sprite)
{
    if (FloatRect(this->sprite->getPosition(), {xPadding, yPadding}).findIntersection(FloatRect(sprite.getTextureRect())))
        return true;
    return false;
}

sf::FloatRect Enemy::getGlobalBounds() const
{
    return sprite->getGlobalBounds();
}

sf::Vector2f Enemy::getPosition() const
{
    return sprite->getPosition();
}

void Enemy::setColor(const sf::Color &color)
{
    sprite->setColor(color);
}

float Enemy::getMaxHealth() const
{
    switch (type)
    {
    case EnemyType::BASIC:
        return 100;
    case EnemyType::FAST:
        return 50;
    case EnemyType::TANK:
        return 300;
    case EnemyType::RANGED:
        return 80;
    default:
        return 100;
    }
}