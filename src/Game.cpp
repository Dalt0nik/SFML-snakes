#include "../Include/Game.h"


// Constructor/Destructor
Game::Game()
{
	this->initVars();
	this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Public

void Game::pollEvents()
{
    //events
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }

    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    /*
        - Clear old frame
        - Render objects
        - Display new frame
    */

    //Clear
    this->window->clear(sf::Color::Green);

    //Draw
    this->window->draw(this->enemy);

    //Display
    this->window->display();
}

// Private

void Game::initVars()
{
	this->window = nullptr;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(480, 480), "Snakes", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(30);
}

void Game::initEnemies()
{
    this->enemy.setPosition(50.f, 50.f);
    this->enemy.setSize(sf::Vector2f(20.f, 20.f));
    this->enemy.setFillColor(sf::Color::Yellow);
    this->enemy.setOutlineColor(sf::Color::Black);
    this->enemy.setOutlineThickness(1.f);
}


// Accessors

const bool Game::running() const
{
	return this->window->isOpen();
}

