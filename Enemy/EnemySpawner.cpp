#include "EnemySpawner.h"
#include <random>
#include <cmath>
#include <algorithm>

EnemySpawner::EnemySpawner(sf::Texture &enemyTexture)
    : enemyTexture(enemyTexture), spawnTimer(0), spawnRate(2.0f), maxEnemies(10) {}

void EnemySpawner::update(float deltaTime, const sf::Sprite &playerSprite)
{
    spawnTimer += deltaTime;

    // Спавн врагов с интервалом
    if (spawnTimer >= spawnRate && enemies.size() < maxEnemies)
    {
        spawnTimer = 0;
        spawnEnemy(getRandomEnemyType(), playerSprite.getPosition());
    }

    // Обновление всех врагов
    for (auto &enemy : enemies)
    {
        enemy->update(deltaTime, playerSprite);
    }

    // Удаление мертвых врагов
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const std::unique_ptr<Enemy> &enemy)
                                 { return !enemy->isAlive(); }),
                  enemies.end());
}

void EnemySpawner::draw(sf::RenderWindow &window)
{
    for (auto &enemy : enemies)
    {
        enemy->draw(window);
    }
}

void EnemySpawner::spawnEnemy(EnemyType type, const sf::Vector2f &playerPos)
{
    sf::Vector2f spawnPos = getSpawnPosition(playerPos);
    enemies.push_back(std::make_unique<Enemy>(type, spawnPos, enemyTexture));
}

sf::Vector2f EnemySpawner::getSpawnPosition(const sf::Vector2f &playerPos)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDist(0, 2 * 3.14159f);
    std::uniform_real_distribution<float> distanceDist(100, 200);

    float angle = angleDist(gen);
    float distance = distanceDist(gen);

    return sf::Vector2f(
        playerPos.x + std::cos(angle) * distance,
        playerPos.y + std::sin(angle) * distance);
}

EnemyType EnemySpawner::getRandomEnemyType()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 3);

    switch (dist(gen))
    {
    case 0:
        return EnemyType::BASIC;
    case 1:
        return EnemyType::FAST;
    case 2:
        return EnemyType::TANK;
    case 3:
        return EnemyType::RANGED;
    default:
        return EnemyType::BASIC;
    }
}