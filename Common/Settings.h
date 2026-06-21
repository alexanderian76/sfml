#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Settings
{
private:
public:
    sf::Vector2u resolution;
    float camZoom = 1.f;
    bool isMute = false;
};