#include "../Include/Enemy.h"
#include <iostream>

//Enemy constructors
Enemy::Enemy() : line(0), shape(sf::RectangleShape()) {}
Enemy::Enemy(int line, sf::RectangleShape shape) : line(line), shape(shape) {}

int Enemy::getLine() const {
    return this->line;
}

sf::RectangleShape& Enemy::getShape(){
    return this->shape;
}

void Enemy::move(float x, float y) {
    this->shape.move(x, y);
}