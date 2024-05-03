#include "EnemyBehavior.h"
#include "Enemy.h"

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