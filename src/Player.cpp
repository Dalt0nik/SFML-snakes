#include "../Include/Player.h"

//Player constructors
Player::Player() : Character() {}
Player::Player(sf::RectangleShape shape) : Character() {
	this->shape = shape;
}

void Player::updateInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->move(-50.f, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->move(0, -50.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->move(50.f, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->move(0, 50.f);
	}
}

void Player::update() {
	
	this->updateInput();
}

