#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include<ctime>

class Game
{
public:
	// Constructor/Destructor
	Game();
	virtual ~Game();


	// Public Functions
	void pollEvents();
	void update();
	void updateEnemies();

	void render();
	void renderEnemies();

	void spawnEnemy();

	// Accessor Functions
	const bool running() const;

private:

	// Variables

	// Window
	sf::RenderWindow* window;
	sf::Event ev;

	// Game Logic

	int score;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	// Game Objects

	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;



	// Functions

	void initVars();
	void initWindow();
	void initEnemies();
};
