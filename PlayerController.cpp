#include "PlayerController.h"
#include <fstream>
#include "utils/utils.h"
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
        if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, sgn(velocity.y) * speed, sgn(velocity.x) * speed))
            canMoveBoth = false;
        if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, sgn(velocity.y) * speed, 0))
            canMoveY = false;
        if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0, sgn(velocity.x) * speed))
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