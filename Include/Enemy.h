#pragma once

#include "EnemyBehavior.h"
#include "Character.h"

#include <ostream>
#include <istream>

/**
 * @class Enemy
 * @brief Represents an enemy character in the game.
 *
 * Manages the behavior, position, and movement of enemies on different lines.
 * Can adopt different behaviors to interact with the player or the environment.
 */
class Enemy : public Character {
public:
    /**
     * @brief Default constructor for the Enemy class.
     *
     * Initializes an empty Enemy object with default values.
     */
    Enemy();

    /**
     * @brief Constructs an Enemy object with a specific line and speed.
     *
     * Initializes the enemy's shape and assigns a PassiveBehavior by default.
     *
     * @param line The line where the enemy will spawn.
     * @param speed The speed of the enemy.
     */
    Enemy(int line, int speed);

    /**
     * @brief Constructs an Enemy object with a specific line, speed, and behavior.
     *
     * Initializes the enemy's shape and assigns the specified behavior.
     *
     * @param line The line where the enemy will spawn.
     * @param speed The speed of the enemy.
     * @param behavior Pointer to the behavior object that will control the enemy.
     */
    Enemy(int line, int speed, EnemyBehavior* behavior);

    /**
     * @brief Updates the enemy's state.
     *
     * Calls the update method of the assigned behavior to control the enemy's movement.
     */
    void update() override;

    /**
     * @brief Sets the line number for the enemy.
     *
     * @param line The line number to assign to the enemy.
     */
    void setLine(int line);

    /**
     * @brief Changes the enemy's behavior to a new type.
     *
     * Updates the behavior of the enemy to a new one while maintaining the current speed.
     *
     * @param newBehavior Pointer to the new behavior object. Must not be null.
     * @throws std::invalid_argument if newBehavior is null.
     */
    void setBehavior(EnemyBehavior* newBehavior);

    /**
     * @brief Checks if the enemy occupies a specific line.
     *
     * @return The line number if the enemy is within a specific range, otherwise 0.
     */
    int takesLine();

    /**
     * @brief Retrieves the current line where the enemy is positioned.
     *
     * @return The line number occupied by the enemy.
     */
    const int getLine() const;

    /**
     * @brief Serializes an Enemy object to an output stream.
     *
     * Writes the enemy's line, shape properties (position, size, colors, outline), and behavior to the output stream.
     *
     * @param os The output stream to write to.
     * @param enemy The enemy object to serialize.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);

    /**
     * @brief Deserializes an Enemy object from an input stream.
     *
     * Reads the enemy's line, shape properties (position, size, colors, outline), and behavior from the input stream.
     *
     * @param is The input stream to read from.
     * @param enemy The enemy object to deserialize into.
     * @return The modified input stream.
     * @throws std::runtime_error if any required data cannot be read or if the behavior type is unknown.
     */
    friend std::istream& operator>>(std::istream& is, Enemy& enemy);

private:
    /**
     * @brief The line number where the enemy is positioned.
     */
    int line;

    /**
     * @brief The behavior controlling the enemy's movement.
     *
     * A unique pointer to an EnemyBehavior object that defines the enemy's behavior.
     */
    std::unique_ptr<EnemyBehavior> behavior;
};
