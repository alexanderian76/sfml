#include "PlayerController.h"
#include <fstream>
using namespace sf;
using namespace std;

const Texture &PlayerController::DrawPlayer(Clock clock, Sprite *sprite)
{
    int j = clock.getElapsedTime().asSeconds() / 0.07f;
    //  std::cout << j << std::endl;
    //  cout << playerRect.size.x << ", " << playerRect.size.y << ": " << j << endl;
    Texture texture;

    // cout << texture.getSize().x << "... " << texture.getSize().y << endl;
    // texture.resize({224, 112});
    // Sprite sprite(texturesIdle[j % 8]);
    //  sprite->setTextureRect(IntRect({0, 0}, {224, 112}));
    // sprite->setPosition({x, y});
    int collisionsCount = 0;
    // cout << j << endl;
    switch (motion)
    {
    case 0:
        texture = texturesIdle[j % 8];

        sprite->setTexture(texturesIdle[j % 8]);
        if (direction == -1)
        {
            // sprite->setTextureRect(playerRect);
            //  texture.resize({playerRect.size.x, playerRect.size.y});
        }
        return texture;
        break;
    case 1:
        texture = texturesAttack1[j % 11];
        sprite->setTexture(texturesAttack1[j % 11]);
        if (direction == -1)
        {
            // sprite->setTextureRect(playerRect);
            //  texture.resize({playerRect.size.x, playerRect.size.y});
        }

        break;
    case 2:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        direction = 1;
        flipRect(sprite);
        //  texture.resize({playerRect.size.x, playerRect.size.y});
        //  sprite->setTextureRect(playerRect);
        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(*sprite, xPadding, yPadding, 0))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveX(1);

        break;
    case 3:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        direction = -1;
        flipRect(sprite);
        // texture.resize({playerRect.size.x, playerRect.size.y});
        // sprite->setTextureRect(playerRect);

        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(*sprite, xPadding, yPadding, 0))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveX(-1);

        break;
    case 4:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        if (direction < 0)
        {
            flipRect(sprite);
            //  texture.resize({playerRect.size.x, playerRect.size.y});
            //   sprite->setTextureRect(playerRect);
        }
        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(*sprite, xPadding, yPadding, -1))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveY(-1);

        break;
    case 5:
        texture = texturesRun[j % 8];
        sprite->setTexture(texturesRun[j % 8]);
        if (direction < 0)
        {
            flipRect(sprite);
            //    texture.resize({playerRect.size.x, playerRect.size.y});
            // sprite->setTextureRect(playerRect);
        }
        for (int i = 0; i < GlobalObjects::objectsCount; i++)
        {
            if (GlobalObjects::objects[i].checkCollision(*sprite, xPadding, yPadding, 1))
                collisionsCount++;
        }
        if (collisionsCount == 0)
            moveY(1);

        break;
    default:
        break;
    }
    if (motion == 1 && j % 11 == 10)
        this->setMotion(0);
    sprite->setPosition(Vector2f(x, y));
    return texture;
    // cout << GlobalObjects::objects[1].checkCollision(sprite, xPadding, yPadding) << endl;

    // sprite->setPosition(Vector2f(x, y));

    // return texture;
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

void PlayerController::flipRect(Sprite *sprite)
{
    std::cout << sprite->getGlobalBounds().size.x << std::endl;
    sf::FloatRect bounds = sprite->getGlobalBounds();

    // sprite->setPosition({direction < 0 ? (bounds.position.x - bounds.size.x) : (bounds.position.x + bounds.size.x), bounds.position.y});

    this->playerRect = IntRect({bounds.position.x, 0}, {bounds.size.x, sprite->getGlobalBounds().size.y});

    // sprite->setScale ->setTextureRect(this->playerRect);
    if (sprite->getScale().x > 0 && direction < 0)
    {
        moveX(bounds.size.x);
    }
    else if(sprite->getScale().x < 0 && direction > 0)
    {
        moveX(-bounds.size.x);
    }
    sprite->setScale(Vector2f(direction * 1.f, 1.f));
}