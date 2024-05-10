#include "../Include/Enemy.h"
#include <iostream>
#include <istream>
#include <ostream>

/**
 * @class Enemy
 * @brief Represents an enemy character in the game.
 *
 * Manages the behavior, position, and movement of enemies on different lines.
 */

 /**
  * @brief Default constructor for the Enemy class.
  *
  * Initializes an empty Enemy object with default values.
  */
Enemy::Enemy() {}

/**
 * @brief Constructs an Enemy object with a specific line and speed.
 *
 * Initializes the enemy's shape and assigns a PassiveBehavior by default.
 *
 * @param line The line where the enemy will spawn.
 * @param speed The speed of the enemy.
 */
Enemy::Enemy(int line, int speed) : behavior(std::make_unique<PassiveBehavior>(speed)) {
    initShape();
    setLine(line);
}

/**
 * @brief Constructs an Enemy object with a specific line, speed, and behavior.
 *
 * Initializes the enemy's shape and assigns the specified behavior.
 *
 * @param line The line where the enemy will spawn.
 * @param speed The speed of the enemy.
 * @param behavior Pointer to the behavior object that will control the enemy.
 */
Enemy::Enemy(int line, int speed, EnemyBehavior* behavior) : behavior(behavior) {
    initShape();
    setLine(line);
}

/**
 * @brief Changes the enemy's behavior to a new type.
 *
 * Updates the behavior of the enemy to a new one while maintaining the current speed.
 *
 * @param newBehavior Pointer to the new behavior object. Must not be null.
 * @throws std::invalid_argument if newBehavior is null.
 */
void Enemy::setBehavior(EnemyBehavior* newBehavior) {
    if (newBehavior == nullptr) {
        throw std::invalid_argument("newBehavior cannot be nullptr");
    }

    int currentSpeed = behavior->speed;
    behavior.reset(newBehavior);
    behavior->speed = currentSpeed;
}

/**
 * @brief Checks if the enemy occupies a specific line.
 *
 * @return The line number if the enemy is within a specific range, otherwise 0.
 */
int Enemy::takesLine() {
    if (this->shape.getPosition().x < 300.f) {
        return this->line;
    }
    else {
        return 0;
    }
}

/**
 * @brief Retrieves the current line where the enemy is positioned.
 *
 * @return The line number occupied by the enemy.
 */
const int Enemy::getLine() const {
    return this->line;
}

/**
 * @brief Sets the line number for the enemy.
 *
 * @param line The line number to assign to the enemy.
 */
void Enemy::setLine(int line) {
    this->line = line;
}

/**
 * @brief Updates the enemy's behavior.
 *
 * Calls the update method of the assigned behavior to control the enemy's movement.
 */
void Enemy::update() {
    this->behavior->update(*this);
}



// Serialization

/**
 * @brief Serializes an Enemy object to an output stream.
 *
 * Writes the enemy's line, shape properties (position, size, colors, outline), and behavior to the output stream.
 *
 * @param os The output stream to write to.
 * @param enemy The enemy object to serialize.
 * @return The modified output stream.
 */
std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    // Write line
    os << enemy.line << ' ';

    // Write the shape properties
    const sf::RectangleShape& shape = enemy.getShape();
    const sf::Vector2f position = shape.getPosition();
    const sf::Vector2f size = shape.getSize();
    const sf::Color fillColor = shape.getFillColor();
    const sf::Color outlineColor = shape.getOutlineColor();
    float outlineThickness = shape.getOutlineThickness();

    // Write position, size, fill color, outline color, and outline thickness
    os << position.x << ' ' << position.y << ' ';
    os << size.x << ' ' << size.y << ' ';
    os << static_cast<int>(fillColor.r) << ' ' << static_cast<int>(fillColor.g) << ' ' << static_cast<int>(fillColor.b) << ' ' << static_cast<int>(fillColor.a) << ' ';
    os << static_cast<int>(outlineColor.r) << ' ' << static_cast<int>(outlineColor.g) << ' ' << static_cast<int>(outlineColor.b) << ' ' << static_cast<int>(outlineColor.a) << ' ';
    os << std::fixed << std::setprecision(1) << outlineThickness << ' ';

    // Write the behavior
    os << *enemy.behavior;

    return os;
}

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
std::istream& operator>>(std::istream& is, Enemy& enemy) {
    // Read the line property
    if (!(is >> enemy.line)) {
        throw std::runtime_error("Failed to read enemy line");
    }

    // Read the shape properties
    sf::Vector2f position, size;
    int fillColorR, fillColorG, fillColorB, fillColorA;
    int outlineColorR, outlineColorG, outlineColorB, outlineColorA;
    float outlineThickness;

    if (!(is >> position.x >> position.y)) {
        throw std::runtime_error("Failed to read shape position");
    }
    if (!(is >> size.x >> size.y)) {
        throw std::runtime_error("Failed to read shape size");
    }
    if (!(is >> fillColorR >> fillColorG >> fillColorB >> fillColorA)) {
        throw std::runtime_error("Failed to read fill color");
    }
    if (!(is >> outlineColorR >> outlineColorG >> outlineColorB >> outlineColorA)) {
        throw std::runtime_error("Failed to read outline color");
    }
    if (!(is >> outlineThickness)) {
        throw std::runtime_error("Failed to read outline thickness");
    }

    // Set the shape properties
    sf::RectangleShape& shape = enemy.getShape();
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(fillColorR, fillColorG, fillColorB, fillColorA));
    shape.setOutlineColor(sf::Color(outlineColorR, outlineColorG, outlineColorB, outlineColorA));
    shape.setOutlineThickness(outlineThickness);

    // Read the behavior type
    int behaviorType;
    if (!(is >> behaviorType)) {
        throw std::runtime_error("Failed to read behavior type");
    }

    // Create the appropriate behavior object
    if (behaviorType == static_cast<int>(BehaviorType::Passive)) {
        enemy.behavior = std::make_unique<PassiveBehavior>();
    }
    else if (behaviorType == static_cast<int>(BehaviorType::Aggressive)) {
        enemy.behavior = std::make_unique<AggressiveBehavior>();
    }
    else {
        throw std::runtime_error("Unknown behavior type: " + std::to_string(behaviorType));
    }

    // Deserialize the behavior
    if (!(is >> *enemy.behavior)) {
        throw std::runtime_error("Failed to read enemy behavior");
    }

    return is;
}


