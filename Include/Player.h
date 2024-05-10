#pragma once
#include "Character.h"

/**
 * @class Player
 * @brief Represents the player character in the game, inheriting from Character.
 *
 * Manages the player's movement, input, and position detection.
 */
class Player : public Character {
public:
    /**
     * @brief Default constructor for the Player class.
     *
     * Initializes an empty Player object with default values.
     */
    Player();

    /**
     * @brief Constructs a Player object with a specified shape.
     *
     * Initializes the player's shape based on the provided rectangle shape.
     *
     * @param shape The rectangle shape to initialize the player's shape.
     */
    Player(sf::RectangleShape shape);

    /**
     * @brief Updates the player state.
     *
     * Calls `updateInput` to process and update the player's movement.
     */
    void update() override;

    /**
     * @brief Updates the player's position based on user input.
     *
     * Processes the movement using keyboard keys (WASD) with a cooldown period between moves.
     */
    void updateInput();

    /**
     * @brief Checks if the player has reached the opposite side of the screen.
     *
     * Determines if the player is at the bottom when moving down or at the top when moving up.
     *
     * @param up Indicates whether the player is moving upwards.
     * @return True if the player has reached the opposite side, otherwise false.
     */
    bool reachedOtherSide(bool up);

    /**
     * @brief Gets the line number where the player is positioned.
     *
     * The line number is calculated based on the player's Y position on the screen.
     *
     * @return The line number occupied by the player.
     */
    int getLine();

private:
    /**
     * @brief Timer to enforce a cooldown period between player moves.
     */
    sf::Clock jumpClock;

    /**
     * @brief Cooldown period between consecutive player moves.
     */
    const sf::Time jumpCooldown = sf::seconds(0.15);
};
