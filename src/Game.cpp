#include "../Include/Game.h"


// Constructor/Destructor
Game::Game()
{
	this->initVars();
	this->initWindow();
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

    this->window->clear(sf::Color::Green);

    //Draw

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
}


// Accessors

const bool Game::running() const
{
	return this->window->isOpen();
}

