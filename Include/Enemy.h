#pragma once

#include "EnemyBehavior.h"
#include "Character.h"

class Enemy : public Character {
public:
    Enemy();
    Enemy(int line, float speed);
    Enemy(int line, float speed, EnemyBehavior* behavior);

    void update() override;
    void setLine(int line);
    void setBehavior(EnemyBehavior* newBehavior);
    int takesLine();
    int getLine();

private:
    int line;
    std::unique_ptr<EnemyBehavior> behavior;
};