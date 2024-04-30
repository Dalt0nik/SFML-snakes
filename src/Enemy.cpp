#include "../Include/Enemy.h"
#include <iostream>

//Enemy constructors

Enemy::Enemy() : Character() {}
Enemy::Enemy(int line, int speed, sf::RectangleShape shape) : Character() {
    this->line = line;
    this->speed = speed;
    this->shape = shape;
}

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

void Enemy::setSpeed(float speed) {
    this->speed = speed;
}

void Enemy::update() {

    this->move(this->speed, 0.f);

}