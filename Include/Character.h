#pragma once
#include <SFML/Graphics.hpp>

//abstract Character class for enemies and player
class Character {
public:
    virtual void update() = 0;
    sf::RectangleShape& getShape();

protected:
    sf::RectangleShape shape;
    void move(float x, float y);
};