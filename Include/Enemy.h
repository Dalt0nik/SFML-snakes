#pragma once

#include "EnemyBehavior.h"
#include "Character.h"

#include <ostream>
#include <istream>

class Enemy : public Character {
public:
    Enemy();
    Enemy(int line, int speed);
    Enemy(int line, int speed, EnemyBehavior* behavior);

    std::unique_ptr<EnemyBehavior> behavior;

    void update() override;
    void setLine(int line);
    void setBehavior(EnemyBehavior* newBehavior);
    int takesLine();
    const int getLine() const;

    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
    friend std::istream& operator>>(std::istream& is, Enemy& enemy);

private:
    int line;
};