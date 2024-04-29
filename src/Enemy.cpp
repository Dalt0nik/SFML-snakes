#include "../Include/Enemy.h"
#include <iostream>

//Enemy constructors
Enemy::Enemy() : line(0), shape(sf::RectangleShape()) {}
Enemy::Enemy(int line, sf::RectangleShape shape) : line(line), shape(shape) {}

//indicates if enemy takes spawn in line, where 0 is none and 1-8 is number of taken line
int Enemy::takesLine() {
    if (this->shape.getPosition().x < 300.f)
    {
        return this->line;
    }
    else return 0;
}

void Enemy::setLine(int line) {
    this->line = line;
}

sf::RectangleShape& Enemy::getShape(){
    return this->shape;
}

void Enemy::move(float x, float y) {
    this->shape.move(x, y);
}