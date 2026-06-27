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
    Sprite *sprite;
    virtual void draw(Clock, RenderWindow &) {};
    virtual void setMotion(int) {};
    virtual int getMotion() { return 0; };
    virtual void moveX(float) {};
    virtual void moveY(float) {};
    virtual void flipRect(Sprite *) {};
    bool isAttack;
    int motion = 0;
    float x = 250, y = 150;
    int direction = 1;
    int currentFrame;
    int health = 100;
    float speed = 4.f;
    Vector2f velocity = sf::Vector2f(0.f, 0.f);
    virtual void setVelocity(Vector2f v) {};
    virtual Vector2f getVelocity() { return Vector2f(0.f,0.f); };
};