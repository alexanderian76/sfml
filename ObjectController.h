#pragma once

#ifndef OBJECT_CONTROLLER_H
#define OBJECT_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "utils/utils.h"

using namespace sf;
using namespace std;

class ObjectController
{
public:
    ObjectController(int x, int y) : sprite(texture)
    {
        this->x = x;
        this->y = y;
        this->rect = IntRect(Vector2i(x, y), Vector2i(width, height));
        if (!isTextureLoaded)
        {
            isTextureLoaded = texture.loadFromFile(getResourcePath() + "877.jpg");
        }
        this->color = Color::Blue;
        this->sprite = Sprite(texture);
        this->sprite.setPosition(Vector2f(x, y));
    }
    int checkCollision(Sprite *, int xPadding, int yPadding, int ySpeed, int xSpeed);
    Sprite drawObject();
    int check = 0;
    Color color;
    static void wall(int startX, int startY, int length, bool isVertical, std::vector<ObjectController> &items)
    {

        int posX = startX;
        int posY = startY;

        for (int i = 0; i < length; i++)
        {

            items.emplace_back(posX, posY);
            if (isVertical)
            {
                posY += 20;
            }
            else
            {
                posX += 20;
            }
        }

    }
    ~ObjectController()
    {
     //   cout << "DELETE OBJECT_CONTROLLER" << endl;
        //  delete sprite;
    }

private:
    IntRect rect;
    int x, y, width = 10, height = 10;
    static Texture texture;
    static bool isTextureLoaded;
    Sprite sprite;
};

#endif