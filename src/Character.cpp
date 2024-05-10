#include "Character.h"

/**
 * @class Character
 * @brief Base class representing a generic character in the game.
 *
 * This class provides fundamental movement and shape manipulation methods for characters.
 */

 /**
  * @brief Moves the character by a specified offset.
  *
  * Changes the character's position by the given X and Y offset values.
  *
  * @param x The offset on the X-axis.
  * @param y The offset on the Y-axis.
  */
void Character::move(float x, float y) {
    shape.move(x, y);
}

/**
 * @brief Retrieves the constant shape of the character.
 *
 * Allows read-only access to the shape data of the character.
 *
 * @return A constant reference to the character's `sf::RectangleShape`.
 */
const sf::RectangleShape& Character::getShape() const {
    return shape;
}

/**
 * @brief Retrieves a modifiable shape of the character.
 *
 * Allows modification of the shape data of the character.
 *
 * @return A reference to the character's `sf::RectangleShape`.
 */
sf::RectangleShape& Character::getShape() {
    return this->shape;
}

/**
 * @brief Initializes the character's shape.
 *
 * Sets up the character's shape using default properties.
 */
void Character::initShape() {
    this->shape = sf::RectangleShape();
}
