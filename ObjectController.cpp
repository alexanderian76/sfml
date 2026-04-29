#include "ObjectController.h"
using namespace sf;
using namespace std;


int ObjectController::checkCollision(Sprite sprite, int xPadding, int yPadding, int ySpeed)
{
    return 0;
   // cout << rect.left << ", " << rect.width << endl; 
    int sign = 1;
    if(sprite.getTextureRect().size.x < 0)
        sign = -1;
    IntRect spriteRect(Vector2i(sprite.getPosition().x + xPadding, sprite.getPosition().y + yPadding), Vector2i(abs(sprite.getTextureRect().size.x) - 2 * xPadding, sprite.getTextureRect().size.y - yPadding));
    IntRect spriteRectNext(Vector2i(sprite.getPosition().x + xPadding + sign * (1 - abs(ySpeed)), sprite.getPosition().y + yPadding + ySpeed), Vector2i(abs(sprite.getTextureRect().size.x) - 2 * xPadding, sprite.getTextureRect().size.y - yPadding));
    
   // cout << spriteRect.left << ", " << spriteRect.width << endl; 
    if(this->rect.findIntersection(spriteRect) || this->rect.findIntersection(spriteRectNext))
        return 1;
    else
        return 0;
}

Sprite ObjectController::drawObject()
{
    Texture texture;
    Sprite sprite(texture);
    //texture.loadFromFile("./01_idle/idle_1.png");
    sprite.setColor(color);
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    
    sprite.setPosition(Vector2f(x, y));
    return sprite;
}