#include "Character.h"


void Character::move(float x, float y) {
    shape.move(x, y);
}

sf::RectangleShape& Character::getShape() {
    return this->shape;
}

void Character::initShape(){
    this->shape = sf::RectangleShape();
}