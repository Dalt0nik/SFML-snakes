#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include<ctime>
#include<Enemy.h>
#include<Player.h>

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
	void renderCharacters();
	void renderScore(sf::RenderTarget* target);

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

	bool goingUp;

	sf::Font font;
	sf::Text text;

	std::vector<int> spawnlines;

	// Game Objects

	std::vector<Enemy> enemies;
	Enemy enemy;
	Player player;



	// Functions

	void initVars();
	void initWindow();
	void initEnemies();
	void initPlayer();
	void initFont();
	void initText();
	void updateSpawnLines();
	void updateText();
};
