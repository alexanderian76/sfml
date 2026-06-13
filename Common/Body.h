#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>

using namespace sf;
using namespace std;

class Body
{
private:
public:
    IntRect rect;
    Sprite* sprite;
    virtual const Texture &draw(Clock, RenderWindow &) {};
    virtual void setMotion(int) {};
    virtual int getMotion() {};
    virtual void moveX(float) {};
    virtual void moveY(float) {};
    virtual void flipRect(Sprite *) {};
    bool isAttack;
    int motion = 0;
    float x = 250, y = 150;
    int direction = 1;
    int currentFrame;
    int health = 100;
    Vector2f velocity = sf::Vector2f(0.f, 0.f);
};