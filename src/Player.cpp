#include "../Include/Player.h"

//Player constructors
Player::Player() : Character() {}
Player::Player(sf::RectangleShape shape) : Character() {
	this->shape = shape;
}

void Player::update() {


}

