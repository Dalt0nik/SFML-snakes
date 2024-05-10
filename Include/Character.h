#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Character
 * @brief Base class representing a generic character in the game.
 *
 * Provides fundamental movement and shape manipulation methods for characters.
 * Acts as a base class for specific types of characters like the player and enemies.
 */
class Character {
public:
    /**
     * @brief Virtual function to update the character state.
     *
     * Must be implemented by derived classes to handle their specific update logic.
     */
    virtual void update() = 0;

    /**
     * @brief Retrieves a modifiable shape of the character.
     *
     * Allows modification of the shape data of the character.
     *
     * @return A reference to the character's `sf::RectangleShape`.
     */
    sf::RectangleShape& getShape();

    /**
     * @brief Retrieves the constant shape of the character.
     *
     * Allows read-only access to the shape data of the character.
     *
     * @return A constant reference to the character's `sf::RectangleShape`.
     */
    const sf::RectangleShape& getShape() const;

    /**
     * @brief Moves the character by a specified offset.
     *
     * Changes the character's position by the given X and Y offset values.
     *
     * @param x The offset on the X-axis.
     * @param y The offset on the Y-axis.
     */
    void move(float x, float y);

protected:
    /**
     * @brief Rectangle shape representing the character.
     *
     * Defines the appearance of the character, including size, position, and color.
     */
    sf::RectangleShape shape;

    /**
     * @brief Initializes the character's shape.
     *
     * Sets up the character's shape using default properties.
     */
    void initShape();
};
