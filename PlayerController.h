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
        cout << sizeof(Texture) << endl;
        texturesAttack1 = (Texture *)calloc(11, sizeof(Texture));
        for (int i = 0; i < 11; i++)
        {
            texturesAttack1[i].loadFromFile("./05_1_atk/1_atk_" + to_string(i + 1) + ".png");
        }

        texturesIdle = (Texture *)calloc(8, sizeof(Texture));
        for (int i = 0; i < 8; i++)
        {
            texturesIdle[i].loadFromFile("./01_idle/idle_" + to_string(i + 1) + ".png");
        }
        cout << texturesIdle[1].getSize().x << endl;
        texturesRun = (Texture *)calloc(8, sizeof(Texture));
        for (int i = 0; i < 8; i++)
        {
            texturesRun[i].loadFromFile("./02_run/run_" + to_string(i + 1) + ".png");
        }
         cout << "texturesRun[1].getSize().x" << endl;
        cout << texturesRun[1].getSize().x << endl;
        playerRect = IntRect({224, 0}, {224, 112});
        motion = 0;
        direction = 1;
        x = 1;
        y = 600;
        cout << texturesIdle[0].getSize().x << endl;
    }
    Texture* texturesAttack1;
    Texture* texturesIdle;
    Texture* texturesRun;
    const Texture& DrawPlayer(Clock, Sprite*);
    void setMotion(int);
    int getMotion();
    void moveX(float);
    void moveY(float);
    void flipRect(Sprite*);
    int motion = 0;
    float x = 50, y = 50;
    IntRect playerRect;
    int direction = 1;
    int currentFrame;
    static const int xPadding = 90;
    static const int yPadding = 60;
    ~PlayerController()
    {
        cout << "DELETE" << endl;
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
    
    
    
};