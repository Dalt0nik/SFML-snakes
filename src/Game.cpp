#include "../Include/Game.h"
#include <iostream>


// Constructor/Destructor
Game::Game()
{
	this->initVars();

	this->initWindow();

    this->initFont();
    this->initText();

    this->initPlayer();
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

    this->player.update();

    if (this->player.reachedOtherSide(this->goingUp))
    {
        /*
        If player reached other side:
        1. increase score
        2. change direction
        3. update text on the screen
        */

        this->score++;
        this->goingUp = !goingUp;
        this->updateText();
    }

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
        this->enemies[i].update();

        if (this->enemies[i].getShape().getPosition().x > this->window->getSize().x) //Deleting enemies if they are out of the screen
        {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::updateText()
{
    this->text.setString("Score:" + std::to_string(this->score));
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

    //Draw characters
    this->renderCharacters();

    //Draw score
    this->renderScore(this->window);

    //Display
    this->window->display();
}

void Game::renderCharacters()
{
    for (auto& enemy : this->enemies)
    {
        this->window->draw(enemy.getShape());
    }

    this->window->draw(this->player.getShape());

}

void Game::renderScore(sf::RenderTarget* target)
{
    target->draw(this->text);
}


void Game::spawnEnemy()
{

    //choose line to spawn
    updateSpawnLines();

    int line = 0;

    do {
        line = rand() % 8 + 1;
    } while (spawnlines[line] == 1);

    this->enemy.setLine(line);


    //choose speed
    int randSpeed = rand() % 10;
    this->enemy.setSpeed(4.f + (static_cast<float>(randSpeed)) / 10);

    // Generate new Enemy
    this->enemy.getShape().setPosition(
        -160.f,
        static_cast<float>(line * 50 + 5) //8 horizontal rows for snakes      
    );
    

    // Spawn the Enemy
    this->enemies.push_back(this->enemy);
}

// Private

void Game::updateSpawnLines()
{
    this->spawnlines = std::vector<int>(9, 0);

    for (auto& enemy : this->enemies)
    {
        if (enemy.takesLine() != 0)
            this->spawnlines[enemy.takesLine()] = 1;
    }

}

void Game::initVars()
{
	this->window = nullptr;

    this->score = 0;
    this->goingUp = false;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 15.f;
    this->maxEnemies = 15;
    this->spawnlines = std::vector<int>(9, 0);
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
    this->enemy.setSpeed(4.f);
}

void Game::initPlayer()
{
    this->player.getShape().setPosition(5.f, 5.f);
    this->player.getShape().setSize(sf::Vector2f(40.f, 40.f));
    this->player.getShape().setFillColor(sf::Color::Red);
    this->player.getShape().setOutlineColor(sf::Color::Black);
    this->player.getShape().setOutlineThickness(1.f);
}

void Game::initFont()
{
    if (!this->font.loadFromFile("Valorax-lg25V.otf"))
    {
        std::cerr << "Error while loading font from ../fonts/Valorax-lg25V.otf";
    }
}

void Game::initText()
{
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(20);
    this->text.setString("Score:" + std::to_string(this->score));
}

// Accessors

const bool Game::running() const
{
	return this->window->isOpen();
}

