#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemy.h"

class EnemySpawner {
public:
    EnemySpawner(sf::Texture& enemyTexture);
    
    void update(float deltaTime, const sf::Sprite& playerSprite);
    void draw(sf::RenderWindow& window);
    void spawnEnemy(EnemyType type, const sf::Vector2f& playerPos);
    
    std::vector<std::unique_ptr<Enemy>>& getEnemies() { return enemies; }
    
    void setSpawnRate(float rate) { spawnRate = rate; }
    void setMaxEnemies(int max) { maxEnemies = max; }

private:
    sf::Texture& enemyTexture;
    std::vector<std::unique_ptr<Enemy>> enemies;
    float spawnTimer;
    float spawnRate;
    int maxEnemies;
    
    sf::Vector2f getSpawnPosition(const sf::Vector2f& playerPos);
    EnemyType getRandomEnemyType();
};