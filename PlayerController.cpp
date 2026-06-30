#include "PlayerController.h"
#include <fstream>
using namespace sf;
using namespace std;

Vector2f PlayerController::validateVelocity()
{
    bool canMoveBoth = true;
    bool canMoveY = true;
    bool canMoveX = true;
    Vector2f localVelocity = {0.f, 0.f};
    for (int i = 0; i < GlobalObjects::objects.size(); i++)
    {
        if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, velocity.y, velocity.x))
            canMoveBoth = false;
        if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, velocity.y, 0))
            canMoveY = false;
        if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0, velocity.x))
            canMoveX = false;
    }
    if (canMoveBoth)
    {
        localVelocity = velocity;
    }
    else if (canMoveX)
    {
        localVelocity.x = velocity.x;
    }
    else if (canMoveY)
    {
        localVelocity.y = velocity.y;
    }
    return localVelocity;
}