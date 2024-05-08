#include "EnemyBehavior.h"
#include "Enemy.h"

#include <istream>
#include <ostream>
#include <iomanip>

EnemyBehavior::EnemyBehavior() = default;
EnemyBehavior::EnemyBehavior(float speed) {
    this->speed = speed;
}

AggressiveBehavior::AggressiveBehavior() = default;
AggressiveBehavior::AggressiveBehavior(float speed) : EnemyBehavior(speed) {}

void AggressiveBehavior::update(Enemy& enemy) {

    //std::srand(static_cast<unsigned>(time(NULL)));
    float additionalSpeed = static_cast<float>((rand() % 4) * 5) / 10;

    enemy.move(this->speed + additionalSpeed, 0.f);

}

PassiveBehavior::PassiveBehavior() = default;
PassiveBehavior::PassiveBehavior(float speed) : EnemyBehavior(speed) {}

void PassiveBehavior::update(Enemy& enemy) {

    enemy.move(this->speed, 0.f);
}


// Serializationw


std::ostream& operator<<(std::ostream& os, const EnemyBehavior& behavior) {
    // Serialize the behavior type
    os << static_cast<int>(behavior.getType()) << ' ';
    // Serialize the speed, with fixed floating point
    os << std::fixed << std::setprecision(1) << behavior.speed;
    return os;
}

std::istream& operator>>(std::istream& is, EnemyBehavior& behavior) {
    // Read the behavior type
    int behaviorType;
    if (!(is >> behaviorType)) {
        throw std::runtime_error("Error reading behavior type");
    }

    // Read the speed
    float speed;
    if (!(is >> speed)) {
        throw std::runtime_error("Error reading behavior speed");
    }

    // Update the behavior object
    behavior.speed = speed;

    return is;
}