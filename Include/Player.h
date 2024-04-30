#pragma once
#include "Character.h"

class Player : public Character {
public:
    Player();
    Player(sf::RectangleShape shape);

    void update() override;


private:
    // Player-specific members
};