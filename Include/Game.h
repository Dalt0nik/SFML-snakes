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


	const bool running() const;

private:

	// Variables

	// Window
	sf::RenderWindow* window;
	sf::Event ev;

	// Game Logic

	bool endgame;

	int score;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float enemyLength;

	bool goingUp;
	bool pause;

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
	void initEnemy(int line);
	void initPlayer();
	void initFont();
	void initText();

	void updateSpawnLines();
	void updateText();
	
	void updateInput();

	void hideEnemies();
	void showEnemies();

	bool isCollision(float playerX, float enemyX);
};
