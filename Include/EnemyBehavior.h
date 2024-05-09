#pragma once

#include<ctime>
#include <ostream>
#include <istream>
#include <iomanip>

class Enemy;

enum class BehaviorType {
    Passive,
    Aggressive
};

class EnemyBehavior {
public:
    EnemyBehavior();
    EnemyBehavior(int speed);
    virtual ~EnemyBehavior() {}
    virtual void update(Enemy& enemy) = 0;
    virtual BehaviorType getType() const = 0;
    int speed;

    friend std::ostream& operator<<(std::ostream& os, const EnemyBehavior& behavior);
    friend std::istream& operator>>(std::istream& is, EnemyBehavior& behavior);
};

class AggressiveBehavior : public EnemyBehavior {
public:
    AggressiveBehavior();
    AggressiveBehavior(int speed);
    void update(Enemy& enemy) override;
    BehaviorType getType() const override { return BehaviorType::Aggressive; }
};

class PassiveBehavior : public EnemyBehavior {
public:
    PassiveBehavior();
    PassiveBehavior(int speed);
    void update(Enemy& enemy) override;
    BehaviorType getType() const override { return BehaviorType::Passive; }
};