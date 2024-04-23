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
        this->window->draw(enemy);
    }
}


void Game::spawnEnemy()
{
    // Generate new Enemy
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
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
    this->enemySpawnTimerMax = 300.f;
    this->maxEnemies = 5;
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(480, 480), "Snakes", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
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

