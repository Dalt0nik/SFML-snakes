#include "../Include/Enemy.h"
#include <iostream>

#include <istream>
#include <ostream>

//Enemy constructors

//Enemy::Enemy() : Character() {}
//Enemy::Enemy(int line, int speed, sf::RectangleShape shape) : Character() {
//    this->line = line;
//    this->shape = shape;
//}

Enemy::Enemy(){}

Enemy::Enemy(int line, float speed) : behavior(std::make_unique<PassiveBehavior>(speed)) {
    initShape();
    setLine(line);
}

Enemy::Enemy(int line, float speed, EnemyBehavior* behavior) : behavior(behavior) {

    initShape();
    setLine(line);
}

void Enemy::setBehavior(EnemyBehavior* newBehavior) { //set new Behavior type

    if (newBehavior == nullptr) {
        throw std::invalid_argument("newBehavior cannot be nullptr");
    }

    float currentSpeed = behavior->speed;
    behavior.reset(newBehavior);
    behavior->speed = currentSpeed;
}


//indicates if enemy takes spawn in line, where 0 is none and 1-8 is number of taken line
int Enemy::takesLine() {
    if (this->shape.getPosition().x < 300.f)
    {
        return this->line;
    }
    else return 0;
}

int Enemy::getLine() {

    return this->line;
}

void Enemy::setLine(int line) {
    this->line = line;
}

void Enemy::update() {

    this->behavior->update(*this);

}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << enemy.line << ' ';
    // Serialize the behavior object
    // You'll need to implement operator<< for EnemyBehavior as well
    os << *enemy.behavior;
    return os;
}

std::istream& operator>>(std::istream& is, Enemy& enemy) {
    is >> enemy.line;

    // Deserialize the behavior object
    is >> *enemy.behavior;
    return is;
}