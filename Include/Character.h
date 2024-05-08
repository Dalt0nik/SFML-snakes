#pragma once
#include <SFML/Graphics.hpp>

//abstract Character class for enemies and player
class Character {
public:
    virtual void update() = 0;

    //2 versions, for changing and for accessing while serializing
    sf::RectangleShape& getShape();
    const sf::RectangleShape& getShape() const;

    void move(float x, float y);

protected:
    sf::RectangleShape shape;
    void initShape();
};