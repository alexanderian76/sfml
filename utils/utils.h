    #pragma once
    #include <SFML/Graphics.hpp>
    
    sf::String toSFString(const std::string &utf8String)
    {
        return sf::String::fromUtf8(utf8String.begin(), utf8String.end());
    }