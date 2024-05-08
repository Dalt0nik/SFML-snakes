#include "Character.h"


void Character::move(float x, float y) {
    shape.move(x, y);
}

const sf::RectangleShape& Character::getShape() const {
    return shape;
}

sf::RectangleShape& Character::getShape() {
    return this->shape;
}

void Character::initShape(){
    this->shape = sf::RectangleShape();
}