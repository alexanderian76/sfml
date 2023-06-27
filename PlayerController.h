#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

#include "GlobalObjects.h"
using namespace sf;
using namespace std;

class PlayerController
{
public:
    PlayerController()
    {
        texturesAttack1 = (Texture *)malloc(sizeof(Texture) * 11);
        for (int i = 0; i < 11; i++)
        {
            texturesAttack1[i].loadFromFile("./05_1_atk/1_atk_" + std::to_string(i + 1) + ".png");
        }

        texturesIdle = (Texture *)malloc(sizeof(Texture) * 8);
        for (int i = 0; i < 8; i++)
        {
            texturesIdle[i].loadFromFile("./01_idle/idle_" + std::to_string(i + 1) + ".png");
        }

        texturesRun = (Texture *)malloc(sizeof(Texture) * 8);
        for (int i = 0; i < 8; i++)
        {
            texturesRun[i].loadFromFile("./02_run/run_" + std::to_string(i + 1) + ".png");
        }
        playerRect = IntRect(224, 0, 224, 112);
        motion = 0;
        direction = 1;
        x = 1;
        y = 600;
    }
    Sprite DrawPlayer(Clock);
    void setMotion(int);
    int getMotion();
    void moveX(float);
    void moveY(float);
    void flipRect(Sprite);
    ~PlayerController()
    {
        delete texturesAttack1;
        delete texturesIdle;
        delete texturesRun;
        direction = NULL;
        x = NULL;
        y = NULL;
        motion = NULL;
        currentFrame = NULL;
        
    }
private:
    Texture *texturesAttack1;
    Texture *texturesIdle;
    Texture *texturesRun;
    int currentFrame;
    int motion;
    float x, y;
    IntRect playerRect;
    int direction;
    static const int xPadding = 70;
    static const int yPadding = 36;
};