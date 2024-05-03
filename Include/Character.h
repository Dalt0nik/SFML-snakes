#pragma once
#include <SFML/Graphics.hpp>

//abstract Character class for enemies and player
class Character {
public:
    virtual void update() = 0;
    sf::RectangleShape& getShape();
    void move(float x, float y);

protected:
    sf::RectangleShape shape;
    void initShape();
};