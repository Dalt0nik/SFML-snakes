#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	// Constructor/Destructor
	Game();
	virtual ~Game();


	// Public Functions
	void pollEvents();
	void update();
	void render();

	// Accessor Functions
	const bool running() const;

private:

	// Variables

	// Window
	sf::RenderWindow* window;
	sf::Event ev;


	// Functions

	void initVars();
	void initWindow();
};
