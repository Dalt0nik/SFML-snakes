#include "../Include/Game.h"
#include <iostream>


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

    this->updateEnemies();
}

void Game::updateEnemies()
{
    //Updating timer and spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) //update timer and spawn
        {
            this->enemySpawnTimer = 0.f;
            this->spawnEnemy();
        }
        else
            this->enemySpawnTimer += 1.f;

    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move(5.f, 0.f);

        if (this->enemies[i].getShape().getPosition().x > this->window->getSize().x) //Deleting enemies if they are out of the screen
        {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
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
    this->renderEnemies();

    //Display
    this->window->display();
}

void Game::renderEnemies()
{
    for (auto& enemy : this->enemies)
    {
        this->window->draw(enemy.getShape());
        std::cout << "draw?\n";
    }
}


void Game::spawnEnemy()
{
    // Generate new Enemy
    this->enemy.getShape().setPosition(
        0.f,
        static_cast<float>((rand() % 8 + 1) * 50 + 10) //8 horizontal rows for snakes      
    );

    // Spawn the Enemy
    this->enemies.push_back(this->enemy);
}

// Private

void Game::initVars()
{
	this->window = nullptr;

    this->score = 0;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 15.f;
    this->maxEnemies = 15;
    this->spawnlines = std::vector<int>(8, 0);
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1000, 500), "Snakes", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    this->enemy.getShape().setPosition(50.f, 50.f);
    this->enemy.getShape().setSize(sf::Vector2f(160.f, 40.f));
    this->enemy.getShape().setFillColor(sf::Color::Yellow);
    this->enemy.getShape().setOutlineColor(sf::Color::Black);
    this->enemy.getShape().setOutlineThickness(1.f);
}


// Accessors

const bool Game::running() const
{
	return this->window->isOpen();
}

