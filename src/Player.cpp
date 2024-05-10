#include "../Include/Player.h"
#include <iostream>

/**
 * @class Player
 * @brief Represents the player character in the game, inheriting from Character.
 *
 * Manages the player's movement, input, and position detection.
 */

 /**
  * @brief Default constructor for the Player class.
  *
  * Initializes an empty Player object with default values.
  */
Player::Player() : Character() {}

/**
 * @brief Constructs a Player object with a specified shape.
 *
 * Initializes the player's shape based on the provided rectangle shape.
 *
 * @param shape The rectangle shape to initialize the player's shape.
 */
Player::Player(sf::RectangleShape shape) : Character() {
    this->shape = shape;
}

/**
 * @brief Updates the player's position based on user input.
 *
 * Processes the movement using the keyboard keys (WASD) with a cooldown period between moves.
 */
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

/**
 * @brief Checks if the player has reached the opposite side of the screen.
 *
 * Determines if the player is at the bottom when moving down or at the top when moving up.
 *
 * @param up Indicates whether the player is moving upwards.
 * @return True if the player has reached the opposite side, otherwise false.
 */
bool Player::reachedOtherSide(bool up) {
    return (!up && this->getLine() == 9) || (up && this->getLine() == 0);
}

/**
 * @brief Gets the line number where the player is positioned.
 *
 * The line number is calculated based on the player's Y position on the screen.
 *
 * @return The line number occupied by the player.
 */
int Player::getLine() {
    return static_cast<int>((this->shape.getPosition().y - 5) / 50.f);
}

/**
 * @brief Updates the player state.
 *
 * Calls `updateInput` to process and update the player's movement.
 */
void Player::update() {
    this->updateInput();
}
