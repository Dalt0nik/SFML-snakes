#pragma once

#include<ctime>

class Enemy;

class EnemyBehavior {
public:
    EnemyBehavior();
    EnemyBehavior(float speed);
    virtual ~EnemyBehavior() {}
    virtual void update(Enemy& enemy) = 0;
    float speed;
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