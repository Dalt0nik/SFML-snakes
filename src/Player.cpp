#include "../Include/Player.h"

//Player constructors
Player::Player() : Character() {}
Player::Player(sf::RectangleShape shape) : Character() {
	this->shape = shape;
}

void Player::updateInput() {
	if (jumpClock.getElapsedTime() > jumpCooldown) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->shape.getPosition().x > 5.f) {
			this->move(-50.f, 0);
			this->jumpClock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->shape.getPosition().y > 5.f) {
			this->move(0, -50.f);
			this->jumpClock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->shape.getPosition().x < 955) {
			this->move(50.f, 0);
			this->jumpClock.restart();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->shape.getPosition().y < 455) {
			this->move(0, 50.f);
			this->jumpClock.restart();
		}
	}
}

bool Player::reachedOtherSide(bool up)
{
	return (!up && this->shape.getPosition().y == 455.f) || (up && this->shape.getPosition().y == 5.f); //not very smart, but it is what it is)
}

void Player::update() {
	
	this->updateInput();
}

