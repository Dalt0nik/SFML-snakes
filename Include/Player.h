#pragma once
#include "Character.h"

class Player : public Character {
public:
    Player();
    Player(sf::RectangleShape shape);

    void update() override;
    void updateInput();

    bool reachedOtherSide(bool up);

    int getLine();


private:
    sf::Clock jumpClock; // Timer for jump cooldown
    const sf::Time jumpCooldown = sf::seconds(0.15); // Cooldown period
};