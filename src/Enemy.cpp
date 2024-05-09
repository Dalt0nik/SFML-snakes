#include "../Include/Enemy.h"
#include <iostream>

#include <istream>
#include <ostream>

//Enemy constructors

Enemy::Enemy(){}

Enemy::Enemy(int line, int speed) : behavior(std::make_unique<PassiveBehavior>(speed)) {
    initShape();
    setLine(line);
}

Enemy::Enemy(int line, int speed, EnemyBehavior* behavior) : behavior(behavior) {

    initShape();
    setLine(line);
}

void Enemy::setBehavior(EnemyBehavior* newBehavior) { //set new Behavior type

    if (newBehavior == nullptr) {
        throw std::invalid_argument("newBehavior cannot be nullptr");
    }

    int currentSpeed = behavior->speed;
    behavior.reset(newBehavior);
    behavior->speed = currentSpeed;
}


//indicates if enemy takes spawn in line, where 0 is none and 1-8 is number of taken line
int Enemy::takesLine() {
    if (this->shape.getPosition().x < 300.f)
    {
        return this->line;
    }
    else return 0;
}

const int Enemy::getLine() const{

    return this->line;
}

void Enemy::setLine(int line) {
    this->line = line;
}

void Enemy::update() {

    this->behavior->update(*this);

}


// Serialization


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

std::istream& operator>>(std::istream& is, Enemy& enemy) {
    // Read the `line` property
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

    // Set the shape properties using the dot operator
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

