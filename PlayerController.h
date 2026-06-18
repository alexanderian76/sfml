#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

#include "GlobalObjects.h"
#include "Common/Body.h"
#include "utils/utils.h"
using namespace sf;
using namespace std;

class PlayerController : public Body
{
private:
public:
    PlayerController()
    {
        cout << sizeof(Texture) << endl;
        texturesAttack1 = new Texture[11];
        for (int i = 0; i < 11; i++)
        {
            texturesAttack1[i].loadFromFile(getResourcePath() + "05_1_atk/1_atk_" + to_string(i + 1) + ".png");
        }

        texturesIdle = new Texture[8];
        for (int i = 0; i < 8; i++)
        {
            texturesIdle[i].loadFromFile(getResourcePath() + "01_idle/idle_" + to_string(i + 1) + ".png");
        }
        cout << texturesIdle[1].getSize().x << endl;
        texturesRun = new Texture[8];
        for (int i = 0; i < 8; i++)
        {
            texturesRun[i].loadFromFile(getResourcePath() + "02_run/run_" + to_string(i + 1) + ".png");
        }

        sprite = new Sprite(texturesIdle[0]);

        sprite->setOrigin({sprite->getLocalBounds().size.x / 2, sprite->getLocalBounds().size.y / 2});

        cout << "texturesRun[1].getSize().x" << endl;
        cout << texturesRun[1].getSize().x << endl;
        rect = IntRect({224, 0}, {224, 112});
        motion = 0;
        direction = 1;
        x = 1000;
        y = 100;
        sprite->setPosition({x, y});
        cout << texturesIdle[0].getSize().x << endl;
    }
    Texture *texturesAttack1;
    Texture *texturesIdle;
    Texture *texturesRun;

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
        delete sprite;
    }

    const Texture &draw(Clock clock, RenderWindow &window) override
    {
        int j = clock.getElapsedTime().asSeconds() / 0.03f;

        Texture texture;

        int collisionsCount = 0;
        isAttack = false;
        Vector2f localVelocity = {0.f, 0.f};
        //this->velocity = {0.f, 0.f};

        if(velocity == Vector2f({0.f, 0.f}) && motion != 1)
        {
            setMotion(0);
        }

        switch (motion)
        {
        case 0:
            texture = texturesIdle[j % 8];

            sprite->setTexture(texturesIdle[j % 8]);

            break;
        case 1:
            texture = texturesAttack1[j % 11];
            sprite->setTexture(texturesAttack1[j % 11]);
            if (j == 4)
            {
                GlobalObjects::camera->shake(8.f, 0.15f);
                isAttack = true;
            }

            break;
        case 2:
        case 3:
        case 4:
        case 5:
            texture = texturesRun[j % 8];
            sprite->setTexture(texturesRun[j % 8]);
            direction = velocity.x != 0 ? velocity.x / abs(velocity.x) : direction;
            flipRect(sprite);
            for (int i = 0; i < GlobalObjects::objects.size(); i++)
            {
                if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, velocity.y, velocity.x))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
            {
                // moveX(2);
               // velocity = {2.f, 0.f};
                localVelocity = velocity;
            }

            break;
      /*  case 3:
            texture = texturesRun[j % 8];
            sprite->setTexture(texturesRun[j % 8]);
            direction = -1;
            flipRect(sprite);

            for (int i = 0; i < GlobalObjects::objects.size(); i++)
            {
                if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 0, -2))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
            {
                // moveX(-2);
                velocity = {-2.f, 0.f};
            }

            break;
        case 4:
            texture = texturesRun[j % 8];
            sprite->setTexture(texturesRun[j % 8]);
            if (direction < 0)
            {
                flipRect(sprite);
            }
            for (int i = 0; i < GlobalObjects::objects.size(); i++)
            {
                if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, -2, 0))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
            {
                // moveY(-2);
                velocity = {0.f, -2.f};
            }

            break;
        case 5:
            texture = texturesRun[j % 8];
            sprite->setTexture(texturesRun[j % 8]);
            if (direction < 0)
            {
                flipRect(sprite);
            }
            for (int i = 0; i < GlobalObjects::objects.size(); i++)
            {
                if (GlobalObjects::objects[i].checkCollision(sprite, xPadding, yPadding, 2, 0))
                    collisionsCount++;
            }
            if (collisionsCount == 0)
            {
                // moveY(2);
                velocity = {0.f, 2.f};
            }

            break;*/
        default:
            break;
        }
        // cout << collisionsCount << endl;
        if (motion == 1 && j % 11 == 10)
            this->setMotion(0);
        sprite->move(localVelocity);

        window.draw(*sprite);
        sf::RectangleShape healthBar(sf::Vector2f(40, 5));
        healthBar.setFillColor(sf::Color::Red);
        healthBar.setPosition({sprite->getPosition().x - 20, sprite->getPosition().y - 30});

        window.draw(healthBar);

        sf::RectangleShape currentHealth(sf::Vector2f(40 * (health / getMaxHealth()), 5));
        currentHealth.setFillColor(sf::Color::Green);
        currentHealth.setPosition({sprite->getPosition().x - 20, sprite->getPosition().y - 30});
        window.draw(currentHealth);

        return texture;
    }

    void setMotion(int newMotion) override
    {
        switch(newMotion)
        {
            case 0:
            case 1:
                velocity = {0.f, 0.f};
                break;
            case 2:
                velocity = velocity.y == 0 ? Vector2f({speed, velocity.y}) : Vector2f({sqrt(speed), velocity.y / abs(velocity.y) * sqrt(speed)});
                break;
            case 3:
                velocity = velocity.y == 0 ? Vector2f({-speed, velocity.y}) : Vector2f({-sqrt(speed), velocity.y / abs(velocity.y) * sqrt(speed)});
                break;
            case 4:
                velocity = velocity.x == 0 ? Vector2f({velocity.x, -speed}) : Vector2f({velocity.x / abs(velocity.x) * sqrt(speed), -sqrt(speed)});
                break;
            case 5:
                velocity = velocity.x == 0 ? Vector2f({velocity.x, speed}) : Vector2f({velocity.x / abs(velocity.x) * sqrt(speed), sqrt(speed)});
                break;
            default:
                break;
        }
        this->motion = newMotion;
    }
    int getMotion() override
    {
        return this->motion;
    }


    void setVelocity(Vector2f v) override
    {
        this->velocity = v;
    }
    Vector2f getVelocity() override
    {
        return this->velocity;
    }

    void moveX(float speed) override
    {

        if (x > 0 && speed < 0)
            this->x = x + speed;
        if (x < GlobalObjects::settings->resolution.x && speed > 0)
            this->x = x + speed;
    }
    void moveY(float speed) override
    {
        this->y = y + speed;
    }

    void flipRect(Sprite *sprite) override
    {
        if (sprite->getScale().x > 0 && direction < 0)
        {
            // moveX(bounds.size.x);
        }
        else if (sprite->getScale().x < 0 && direction > 0)
        {
            //  moveX(-bounds.size.x);
        }
        sprite->setScale(Vector2f(direction * 1.f, 1.f));
    }
};