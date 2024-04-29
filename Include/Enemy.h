#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy();
    Enemy(int line, sf::RectangleShape shape);
    int takesLine();
    void setLine(int line);
    sf::RectangleShape& getShape();
    void move(float x, float y);

private:
    int line;
    sf::RectangleShape shape;
};

#endif // ENEMY_H