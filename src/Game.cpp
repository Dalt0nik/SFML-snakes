#include "../Include/Game.h"
#include <iostream>
#include <fstream>


// Constructor/Destructor
Game::Game()
{
	this->initVars();

	this->initWindow();

    this->initFont();
    this->initText();

    this->initPlayer();
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
    
    this->updateInput();

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

    if(!this->pause)
        this->updateEnemies();
}

void Game::updateInput()
{
    static sf::Clock clock; // Clock to measure time since last key press
    sf::Time elapsedTime = clock.getElapsedTime(); // Time since last key press

    // Only process key press if at least 500 milliseconds have passed
    if (elapsedTime.asMilliseconds() > 500) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (this->pause)
                this->showEnemies();
            else
                this->hideEnemies();

            this->pause = !(this->pause);

            clock.restart(); // Reset the clock
        }
    }
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
    
    for (int i = this->enemies.size() - 1; i >= 0; --i)
    {
        this->enemies[i].update();

        //get enemy X position
        float enemyPosition = this->enemies[i].getShape().getPosition().x;

        if(this->enemies[i].getLine() == this->player.getLine() && this->isCollision(this->player.getShape().getPosition().x, enemyPosition))
            this->endgame = true;

        if (enemyPosition > this->window->getSize().x) //Deleting enemies if they are out of the screen
        {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

// returns true if player and enemy collides (consired they are in the same line)
bool Game::isCollision(float playerX, float enemyX)
{
    if (playerX > enemyX && playerX < enemyX + this->enemyLength)
        return true;
    else if (playerX < enemyX && playerX + 50.f > enemyX)
        return true;
    else return false;

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


    //choose random speed
    int randSpeed = (40 + rand() % 10);

    // Generate new Enemy
    Enemy enemy = Enemy(line, randSpeed);

    this->initEnemy(&enemy, line);

    if (line == 1 || line == 8)
        enemy.setBehavior(new AggressiveBehavior());
    
    // Spawn the Enemy
    this->enemies.push_back(std::move(enemy));
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

void Game::hideEnemies() {

    std::ofstream file("enemies.dat");
    if (file.is_open()) {

        file << this->enemies.size() << '\n';   // Write the number of enemies to the file
        
        for (const Enemy& enemy : this->enemies) {  // Write each enemy to the file
            file << enemy << '\n';
        }
        file.close();
    }

    this->enemies.clear();
}

void Game::showEnemies() {
    std::ifstream file("enemies.dat");
    if (file.is_open()) {
        
        size_t numEnemies;
        file >> numEnemies; // Read the number of enemies from the file
        
        this->enemies.clear();
        for (size_t i = 0; i < numEnemies; ++i) {   // Read each enemy from the file
            Enemy enemy;
            file >> enemy;
            
            this->enemies.push_back(std::move(enemy));
        }
        file.close();
    }
}

void Game::initVars()
{
	this->window = nullptr;

    this->endgame = false;
    this->pause = false;

    this->score = 0;
    this->goingUp = false;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 15.f;
    this->maxEnemies = 15;
    this->enemyLength = 160.f;
    this->spawnlines = std::vector<int>(9, 0);
}

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1000, 500), "Snakes", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemy(Enemy* enemy, int line)
{
    enemy->getShape().setPosition(
        -160.f,
        static_cast<float>(line * 50 + 5) //8 horizontal rows for snakes      
    );
    enemy->getShape().setSize(sf::Vector2f(this->enemyLength, 40.f));
    enemy->getShape().setFillColor(sf::Color::Yellow);
    enemy->getShape().setOutlineColor(sf::Color::Black);
    enemy->getShape().setOutlineThickness(1.f);

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

const bool Game::running() const
{
	return this->window->isOpen() && !this->endgame;
}

