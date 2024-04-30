//#pragma once
//
#pragma once
#include "Character.h"

class Enemy : public Character {
public:
    Enemy();
    Enemy(int line,int speed, sf::RectangleShape shape);

    void update() override;
    void setLine(int line);
    void setSpeed(float speed);
    int takesLine();

private:
    float speed;
    int line;
};