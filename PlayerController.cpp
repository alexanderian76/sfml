#include "PlayerController.h"

using namespace sf;
using namespace std;

Sprite PlayerController::DrawPlayer(Clock clock)
{
    int j = clock.getElapsedTime().asSeconds() / 0.07f;
    Sprite sprite;
    sprite.setPosition(x, y);
    int collisionsCount = 0;
    switch (motion)
    {
    case 0:
        sprite.setTexture(texturesIdle[j % 8]);
        if (direction == -1)
            sprite.setTextureRect(playerRect);
        break;
    case 1:
        sprite.setTexture(texturesAttack1[j % 11]);
        if (direction == -1)
            sprite.setTextureRect(playerRect);
        break;
    case 2:
        sprite.setTexture(texturesRun[j % 8]);
        direction = 1;

        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveX(0.1);
        break;
    case 3:
        sprite.setTexture(texturesRun[j % 8]);
        direction = -1;
        flipRect(sprite);
        sprite.setTextureRect(playerRect);

        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveX(-0.1);
        break;
    case 4:
        sprite.setTexture(texturesRun[j % 8]);
        if (direction < 0)
        {
            flipRect(sprite);
            sprite.setTextureRect(playerRect);
        }
        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, -1))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveY(-0.1);
        break;
    case 5:
        sprite.setTexture(texturesRun[j % 8]);
        if (direction < 0)
        {
            flipRect(sprite);

            sprite.setTextureRect(playerRect);
        }
        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 1))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveY(0.1);
        break;
    default:
        break;
    }
    // cout << GlobalObjects::objects[1].checkCollision(sprite, xPadding, yPadding) << endl;
    if (motion == 1 && j % 11 == 10)
        this->setMotion(0);
    sprite.setPosition(x, y);
    return sprite;
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
    if (x + xPadding > 0 && speed < 0)
        this->x = x + speed;
    if (x + xPadding < 800 && speed > 0)
        this->x = x + speed;
}
void PlayerController::moveY(float speed)
{
    this->y = y + speed;
}

void PlayerController::flipRect(Sprite sprite)
{
    this->playerRect = IntRect(sprite.getGlobalBounds().width, 0, direction * sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}