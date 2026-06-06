#include "PlayerController.h"
#include <fstream>
using namespace sf;
using namespace std;

const Texture &PlayerController::DrawPlayer(Clock clock, Sprite *sprite, RenderWindow &window)
{
    int j = clock.getElapsedTime().asSeconds() / 0.03f;

    Texture texture;

    int collisionsCount = 0;
    isAttack = false;
    switch (motion)
    {
    case 0:
        texture = texturesIdle[j % 8];

        sprite->setTexture(texturesIdle[j % 8]);

        break;
    case 1:
        texture = texturesAttack1[j % 11];
        sprite->setTexture(texturesAttack1[j % 11]);
        if (j == 4)
            isAttack = true;

        break;
    case 2:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        direction = 1;
        flipRect(sprite);
        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0, 2))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveX(2);

        break;
    case 3:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        direction = -1;
        flipRect(sprite);

        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0, -2))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveX(-2);

        break;
    case 4:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        if (direction < 0)
        {
            flipRect(sprite);
        }
        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, -2, 0))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveY(-2);

        break;
    case 5:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        if (direction < 0)
        {
            flipRect(sprite);
        }
        for (int i = 0; i < GlobalObjects::objects.size(); i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 2, 0))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveY(2);

        break;
    default:
        break;
    }
    // cout << collisionsCount << endl;
    if (motion == 1 && j % 11 == 10)
        this->setMotion(0);
    sprite->setPosition(Vector2f(x, y));

    window.draw(*sprite);
    sf::RectangleShape healthBar(sf::Vector2f(40, 5));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition({sprite->getPosition().x - 20, sprite->getPosition().y - 30});

    window.draw(healthBar);

    sf::RectangleShape currentHealth(sf::Vector2f(40 * (health / getMaxHealth()), 5));
    currentHealth.setFillColor(sf::Color::Green);
    currentHealth.setPosition({sprite->getPosition().x - 20, sprite->getPosition().y - 30});
    window.draw(currentHealth);

    return texture;
}

void PlayerController::setMotion(int newMotion)
{
    this->motion = newMotion;
}
int PlayerController::getMotion()
{
    return this->motion;
}
void PlayerController::moveX(float speed)
{

    if (x > 0 && speed < 0)
        this->x = x + speed;
    if (x < GlobalObjects::screenWidth && speed > 0)
        this->x = x + speed;
}
void PlayerController::moveY(float speed)
{
    this->y = y + speed;
}

void PlayerController::flipRect(Sprite *sprite)
{
    if (sprite->getScale().x > 0 && direction < 0)
    {
        // moveX(bounds.size.x);
    }
    else if (sprite->getScale().x < 0 && direction > 0)
    {
        //  moveX(-bounds.size.x);
    }
    sprite->setScale(Vector2f(direction * 1.f, 1.f));
}