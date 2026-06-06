#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

#include "GlobalObjects.h"
using namespace sf;
using namespace std;

class PlayerController
{
private:
public:
    PlayerController()
    {
        cout << sizeof(Texture) << endl;
        texturesAttack1 = new Texture[11];
        for (int i = 0; i < 11; i++)
        {
            texturesAttack1[i].loadFromFile("./05_1_atk/1_atk_" + to_string(i + 1) + ".png");
        }

        texturesIdle = new Texture[8];
        for (int i = 0; i < 8; i++)
        {
            texturesIdle[i].loadFromFile("./01_idle/idle_" + to_string(i + 1) + ".png");
        }
        cout << texturesIdle[1].getSize().x << endl;
        texturesRun = new Texture[8];
        for (int i = 0; i < 8; i++)
        {
            texturesRun[i].loadFromFile("./02_run/run_" + to_string(i + 1) + ".png");
        }
        cout << "texturesRun[1].getSize().x" << endl;
        cout << texturesRun[1].getSize().x << endl;
        playerRect = IntRect({224, 0}, {224, 112});
        motion = 0;
        direction = 1;
        x = 450;
        y = 400;
        cout << texturesIdle[0].getSize().x << endl;
    }
    Texture *texturesAttack1;
    Texture *texturesIdle;
    Texture *texturesRun;
    const Texture &DrawPlayer(Clock, Sprite *, RenderWindow &);
    void setMotion(int);
    int getMotion();
    void moveX(float);
    void moveY(float);
    void flipRect(Sprite *);
    bool isAttack;
    int motion = 0;
    float x = 250, y = 150;
    IntRect playerRect;
    int direction = 1;
    int currentFrame;
    int health = 100;
    Vector2f playerVelocity = sf::Vector2f(0.f, 0.f);
    float getMaxHealth() const
    {
        return 100;
    };
    static const int xPadding = 90;
    static const int yPadding = 60;
    ~PlayerController()
    {
     //   cout << "DELETE" << endl;
        delete[] texturesAttack1;
        delete[] texturesIdle;
        delete[] texturesRun;

    }
};