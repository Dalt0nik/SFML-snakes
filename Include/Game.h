#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include<ctime>
#include<Enemy.h>

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

	std::vector<int> spawnlines;

	// Game Objects

	std::vector<Enemy> enemies;
	Enemy enemy;



	// Functions

	void initVars();
	void initWindow();
	void initEnemies();
};
