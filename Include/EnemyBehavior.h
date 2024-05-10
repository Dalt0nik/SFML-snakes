#pragma once

#include <ctime>
#include <ostream>
#include <istream>
#include <iomanip>

class Enemy;

/**
 * @enum BehaviorType
 * @brief Enumerates different behavior types for enemies.
 */
enum class BehaviorType {
    Passive,    /**< Represents passive enemy behavior */
    Aggressive  /**< Represents aggressive enemy behavior */
};

/**
 * @class EnemyBehavior
 * @brief Base class that defines the behavior of an enemy character.
 *
 * Provides the base implementation for different enemy behaviors.
 */
class EnemyBehavior {
public:
    /**
     * @brief Default constructor for EnemyBehavior.
     */
    EnemyBehavior();

    /**
     * @brief Constructor that sets the speed of the enemy behavior.
     *
     * @param speed The speed value to initialize the behavior with.
     */
    EnemyBehavior(int speed);

    /**
     * @brief Virtual destructor for EnemyBehavior.
     */
    virtual ~EnemyBehavior() {}

    /**
     * @brief Pure virtual method that updates the enemy behavior.
     *
     * This method must be implemented by derived classes to define how the enemy moves.
     *
     * @param enemy Reference to the enemy object to update.
     */
    virtual void update(Enemy& enemy) = 0;

    /**
     * @brief Pure virtual method to return the behavior type.
     *
     * Must be implemented in derived classes to identify the type of behavior.
     *
     * @return The BehaviorType enumeration value representing the behavior type.
     */
    virtual BehaviorType getType() const = 0;

    /**
     * @brief The speed associated with this behavior.
     */
    int speed;

    /**
     * @brief Serializes an EnemyBehavior object to an output stream.
     *
     * Writes the behavior type and speed to the output stream.
     *
     * @param os The output stream to write to.
     * @param behavior The behavior object to serialize.
     * @return The modified output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const EnemyBehavior& behavior);

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
    friend std::istream& operator>>(std::istream& is, EnemyBehavior& behavior);
};

/**
 * @class AggressiveBehavior
 * @brief Implements an aggressive movement pattern for enemies.
 *
 * Aggressive behavior makes the enemy move quickly and erratically.
 */
class AggressiveBehavior : public EnemyBehavior {
public:
    /**
     * @brief Default constructor for AggressiveBehavior.
     */
    AggressiveBehavior();

    /**
     * @brief Constructs AggressiveBehavior with a specific speed.
     *
     * @param speed The speed value to initialize the aggressive behavior with.
     */
    AggressiveBehavior(int speed);

    /**
     * @brief Updates the enemy's position using aggressive movement.
     *
     * Moves the enemy with a randomized speed based on the configured behavior.
     *
     * @param enemy Reference to the enemy object to update.
     */
    void update(Enemy& enemy) override;

    /**
     * @brief Returns the behavior type for aggressive enemies.
     *
     * @return The BehaviorType enumeration value for Aggressive behavior.
     */
    BehaviorType getType() const override { return BehaviorType::Aggressive; }
};

/**
 * @class PassiveBehavior
 * @brief Implements a passive movement pattern for enemies.
 *
 * Passive behavior makes the enemy move at a steady, predictable pace.
 */
class PassiveBehavior : public EnemyBehavior {
public:
    /**
     * @brief Default constructor for PassiveBehavior.
     */
    PassiveBehavior();

    /**
     * @brief Constructs PassiveBehavior with a specific speed.
     *
     * @param speed The speed value to initialize the passive behavior with.
     */
    PassiveBehavior(int speed);

    /**
     * @brief Updates the enemy's position using passive movement.
     *
     * Moves the enemy at a constant speed based on the configured behavior.
     *
     * @param enemy Reference to the enemy object to update.
     */
    void update(Enemy& enemy) override;

    /**
     * @brief Returns the behavior type for passive enemies.
     *
     * @return The BehaviorType enumeration value for Passive behavior.
     */
    BehaviorType getType() const override { return BehaviorType::Passive; }
};
