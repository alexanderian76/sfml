#include "ObjectController.h"
using namespace sf;
using namespace std;


int ObjectController::checkCollision(Sprite sprite, int xPadding, int yPadding, int ySpeed)
{
   // cout << rect.left << ", " << rect.width << endl; 
    int sign = 1;
    if(sprite.getTextureRect().width < 0)
        sign = -1;
    IntRect spriteRect(Vector2i(sprite.getPosition().x + xPadding, sprite.getPosition().y + yPadding), Vector2i(abs(sprite.getTextureRect().width) - 2 * xPadding, sprite.getTextureRect().height - yPadding));
    IntRect spriteRectNext(Vector2i(sprite.getPosition().x + xPadding + sign * (1 - abs(ySpeed)), sprite.getPosition().y + yPadding + ySpeed), Vector2i(abs(sprite.getTextureRect().width) - 2 * xPadding, sprite.getTextureRect().height - yPadding));
    
   // cout << spriteRect.left << ", " << spriteRect.width << endl; 
    if(this->rect.intersects(spriteRect) || this->rect.intersects(spriteRectNext))
        return 1;
    else
        return 0;
}

Sprite ObjectController::drawObject()
{
    Sprite sprite;
    Texture texture;
    
    //texture.loadFromFile("./01_idle/idle_1.png");
    sprite.setColor(color);
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
    
    sprite.setPosition(x, y);
    return sprite;
}