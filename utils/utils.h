#pragma once
#include <SFML/Graphics.hpp>


std::string getResourcePath();

sf::String toSFString(const std::string &utf8String);

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}