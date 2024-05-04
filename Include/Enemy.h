#pragma once

#include "EnemyBehavior.h"
#include "Character.h"

#include <ostream>
#include <istream>

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

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
    friend std::istream& operator>>(std::istream& is, Enemy& enemy);

private:
    int line;
    std::unique_ptr<EnemyBehavior> behavior;
};