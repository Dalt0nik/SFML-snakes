#include "EnemyBehavior.h"
#include "Enemy.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>

/**
 * @class EnemyBehavior
 * @brief Base class that defines the behavior of an enemy character.
 *
 * Provides the base implementation for different enemy behaviors.
 */

 /**
  * @brief Default constructor for EnemyBehavior.
  */
EnemyBehavior::EnemyBehavior() = default;

/**
 * @brief Constructor that sets the speed of the enemy behavior.
 *
 * @param speed The speed value to initialize the behavior with.
 */
EnemyBehavior::EnemyBehavior(int speed) {
    this->speed = speed;
}

/**
 * @class AggressiveBehavior
 * @brief Implements an aggressive movement pattern for enemies.
 *
 * Aggressive behavior makes the enemy move quickly and erratically.
 */

 /**
  * @brief Default constructor for AggressiveBehavior.
  */
AggressiveBehavior::AggressiveBehavior() = default;

/**
 * @brief Constructs AggressiveBehavior with a specific speed.
 *
 * @param speed The speed value to initialize the aggressive behavior with.
 */
AggressiveBehavior::AggressiveBehavior(int speed) : EnemyBehavior(speed) {}

/**
 * @brief Updates the enemy's position using aggressive movement.
 *
 * Moves the enemy with a randomized speed based on the configured behavior.
 *
 * @param enemy Reference to the enemy object to update.
 */
void AggressiveBehavior::update(Enemy& enemy) {
    float finalSpeed = static_cast<float>((rand() % 3) * 20 + this->speed) / 10;
    float stop = static_cast<float>(rand() % 2);
    enemy.move(finalSpeed * stop, 0.f);
}

/**
 * @class PassiveBehavior
 * @brief Implements a passive movement pattern for enemies.
 *
 * Passive behavior makes the enemy move at a steady, predictable pace.
 */

 /**
  * @brief Default constructor for PassiveBehavior.
  */
PassiveBehavior::PassiveBehavior() = default;

/**
 * @brief Constructs PassiveBehavior with a specific speed.
 *
 * @param speed The speed value to initialize the passive behavior with.
 */
PassiveBehavior::PassiveBehavior(int speed) : EnemyBehavior(speed) {}

/**
 * @brief Updates the enemy's position using passive movement.
 *
 * Moves the enemy at a constant speed based on the configured behavior.
 *
 * @param enemy Reference to the enemy object to update.
 */
void PassiveBehavior::update(Enemy& enemy) {
    enemy.move(static_cast<float>(this->speed) / 10, 0.f);
}

// Serialization

/**
 * @brief Serializes an EnemyBehavior object to an output stream.
 *
 * Writes the behavior type and speed to the output stream.
 *
 * @param os The output stream to write to.
 * @param behavior The behavior object to serialize.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const EnemyBehavior& behavior) {
    // Serialize the behavior type
    os << static_cast<int>(behavior.getType()) << ' ';
    // Serialize the speed, with fixed floating point
    os << std::fixed << std::setprecision(1) << behavior.speed;
    return os;
}

/**
 * @brief Deserializes an EnemyBehavior object from an input stream.
 *
 * Reads the behavior type and speed from the input stream and updates the behavior.
 *
 * @param is The input stream to read from.
 * @param behavior The behavior object to deserialize into.
 * @return The modified input stream.
 * @throws std::runtime_error if the speed cannot be read.
 */
std::istream& operator>>(std::istream& is, EnemyBehavior& behavior) {
    // Read the speed
    int speed;
    if (!(is >> speed)) {
        throw std::runtime_error("Error reading behavior speed");
    }

    // Update speed
    behavior.speed = speed;

    return is;
}
