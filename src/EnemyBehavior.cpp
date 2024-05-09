#include "EnemyBehavior.h"
#include "Enemy.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>

EnemyBehavior::EnemyBehavior() = default;
EnemyBehavior::EnemyBehavior(int speed) {
    this->speed = speed;
}

AggressiveBehavior::AggressiveBehavior() = default;
AggressiveBehavior::AggressiveBehavior(int speed) : EnemyBehavior(speed) {}

void AggressiveBehavior::update(Enemy& enemy) {

    float finalSpeed = static_cast<float>((rand() % 3) * 20 + this->speed) / 10;
    float stop = static_cast<float>(rand() % 2);
    enemy.move(finalSpeed * stop, 0.f);

}

PassiveBehavior::PassiveBehavior() = default;
PassiveBehavior::PassiveBehavior(int speed) : EnemyBehavior(speed) {}

void PassiveBehavior::update(Enemy& enemy) {

    enemy.move(static_cast<float>(this->speed) / 10, 0.f);
}


// Serialization

std::ostream& operator<<(std::ostream& os, const EnemyBehavior& behavior) {
    // Serialize the behavior type
    os << static_cast<int>(behavior.getType()) << ' ';
    // Serialize the speed, with fixed floating point
    os << std::fixed << std::setprecision(1) << behavior.speed;
    return os;
}

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