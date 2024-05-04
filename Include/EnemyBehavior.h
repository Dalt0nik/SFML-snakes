#pragma once

#include<ctime>
#include <ostream>
#include <istream>

class Enemy;

class EnemyBehavior {
public:
    EnemyBehavior();
    EnemyBehavior(float speed);
    virtual ~EnemyBehavior() {}
    virtual void update(Enemy& enemy) = 0;
    float speed;

    friend std::ostream& operator<<(std::ostream& os, const EnemyBehavior& behavior);
    friend std::istream& operator>>(std::istream& is, EnemyBehavior& behavior);
};

class AggressiveBehavior : public EnemyBehavior {
public:
    AggressiveBehavior();
    AggressiveBehavior(float speed);
    void update(Enemy& enemy) override;
};

class PassiveBehavior : public EnemyBehavior {
public:
    PassiveBehavior();
    PassiveBehavior(float speed);
    void update(Enemy& enemy) override;
};