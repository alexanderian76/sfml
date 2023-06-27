#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace sf;
using namespace std;

class ObjectController
{
public:
    ObjectController(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->rect = IntRect(Vector2i(x, y), Vector2i(width, height));
        this->color = Color::Blue;
    }
    int checkCollision(Sprite, int xPadding, int yPadding, int ySpeed);
    Sprite drawObject();
    int check = 0;
    ~ObjectController()
    {
        x = NULL;
        y = NULL;

    }
private:
    IntRect rect;
    int x, y, width, height;
    Color color;

};