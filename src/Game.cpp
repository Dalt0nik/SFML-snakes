#include "../Include/Game.h"
#include <iostream>
#include <fstream>

/**
 * @class Game
 * @brief Manages the overall game setup, loop, and termination.
 */

 /**
  * @brief Default constructor for the Game class.
  *
  * Initializes game components such as window, fonts, text, and player.
  */
Game::Game()
{
    this->initVars();
    this->initWindow();
    this->initFont();
    this->initText();
    this->initPlayer();
}

/**
 * @brief Destructor for the Game class.
 *
 * Cleans up dynamic resources by deleting the window object.
 */
Game::~Game()
{
    delete this->window;
}

/**
 * @brief Handles all system events for the game.
 *
 * Polls for system events like window close and keyboard key presses.
 */
void Game::pollEvents()
{
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

/**
 * @brief Updates game state, player movement, and enemies.
 *
 * Manages events, input processing, player movement, and enemy updates.
 * Checks if the player has reached the other side and toggles direction.
 */
void Game::update()
{
    this->pollEvents();
    this->updateInput();
    this->player.update();

    if (this->player.reachedOtherSide(this->goingUp))
    {
        this->score++;
        this->goingUp = !this->goingUp;
        this->updateText();
    }

    if (!this->pause)
        this->updateEnemies();
}

/**
 * @brief Processes user input for pausing and resuming the game.
 *
 * Monitors keyboard events, specifically the spacebar, to toggle game pause.
 */
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

/**
 * @brief Updates enemies' movement and manages their lifecycle.
 *
 * Handles enemy spawning, movement, and removal based on their position and interactions with the player.
 */
void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
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

        float enemyPosition = this->enemies[i].getShape().getPosition().x;
        if (this->enemies[i].getLine() == this->player.getLine() && this->isCollision(this->player.getShape().getPosition().x, enemyPosition))
            this->endgame = true;

        if (enemyPosition > this->window->getSize().x)
            this->enemies.erase(this->enemies.begin() + i);
    }
}

/**
 * @brief Checks if the player and enemy collide.
 *
 * @param playerX The X-coordinate of the player.
 * @param enemyX The X-coordinate of the enemy.
 * @return True if the player and enemy collide, otherwise false.
 */
bool Game::isCollision(float playerX, float enemyX)
{
    if (playerX > enemyX && playerX < enemyX + this->enemyLength)
        return true;
    else if (playerX < enemyX && playerX + 50.f > enemyX)
        return true;
    else
        return false;
}

/**
 * @brief Updates the game score text.
 *
 * Sets the game score text based on the current score.
 */
void Game::updateText()
{
    this->text.setString("Score: " + std::to_string(this->score));
}

/**
 * @brief Renders all game components onto the screen.
 *
 * Clears the screen, then draws all characters and score text before displaying the updated frame.
 */
void Game::render()
{
    this->window->clear(sf::Color::Green);
    this->renderCharacters();
    this->renderScore(this->window);
    this->window->display();
}

/**
 * @brief Renders all game characters onto the screen.
 *
 * Draws both the player and enemies onto the screen.
 */
void Game::renderCharacters()
{
    for (auto& enemy : this->enemies)
    {
        this->window->draw(enemy.getShape());
    }

    this->window->draw(this->player.getShape());
}

/**
 * @brief Renders the game score onto the specified render target.
 *
 * @param target The render target where the score will be drawn.
 */
void Game::renderScore(sf::RenderTarget* target)
{
    target->draw(this->text);
}

/**
 * @brief Spawns a new enemy in a random available line with a random speed.
 *
 * Uses an available line to create and initialize a new enemy and optionally sets aggressive behavior.
 */
void Game::spawnEnemy()
{
    this->updateSpawnLines();

    int line = 0;
    do {
        line = rand() % 8 + 1;
    } while (this->spawnlines[line] == 1);

    int randSpeed = 40 + rand() % 10;
    Enemy enemy(line, randSpeed);
    this->initEnemy(&enemy, line);

    if (line == 1 || line == 8)
        enemy.setBehavior(new AggressiveBehavior());

    this->enemies.push_back(std::move(enemy));
}


// Private

/**
 * @brief Updates the available lines for enemy spawning.
 *
 * Initializes a vector that keeps track of which lines are available for spawning and marks each taken line based on existing enemies.
 */
void Game::updateSpawnLines()
{
    this->spawnlines = std::vector<int>(9, 0);

    for (auto& enemy : this->enemies)
    {
        if (enemy.takesLine() != 0)
            this->spawnlines[enemy.takesLine()] = 1;
    }
}

/**
 * @brief Serializes and hides all enemies by saving them to a file.
 *
 * Saves the current state of all enemies to a file and clears the enemy vector afterward.
 */
void Game::hideEnemies()
{
    std::ofstream file("enemies.dat");
    if (file.is_open())
    {
        file << this->enemies.size() << '\n'; // Write the number of enemies to the file

        for (const Enemy& enemy : this->enemies) // Write each enemy to the file
        {
            file << enemy << '\n';
        }
        file.close();
    }

    this->enemies.clear();
}

/**
 * @brief Deserializes and shows all enemies from a file.
 *
 * Loads the enemies from a file and populates the vector with their state.
 */
void Game::showEnemies()
{
    std::ifstream file("enemies.dat");
    if (file.is_open())
    {
        size_t numEnemies;
        file >> numEnemies; // Read the number of enemies from the file

        this->enemies.clear();
        for (size_t i = 0; i < numEnemies; ++i) // Read each enemy from the file
        {
            Enemy enemy;
            file >> enemy;

            this->enemies.push_back(std::move(enemy));
        }
        file.close();
    }
}

/**
 * @brief Initializes default game variables.
 *
 * Sets up initial values for game variables like score, enemy spawn timers, maximum enemies, and more.
 */
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

/**
 * @brief Initializes the main game window.
 *
 * Sets up the game window with a title and framerate limit.
 */
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1000, 500), "Snakes", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

/**
 * @brief Initializes the properties of an enemy based on a specific line.
 *
 * @param enemy Pointer to the Enemy object to initialize.
 * @param line The line number where the enemy will spawn.
 */
void Game::initEnemy(Enemy* enemy, int line)
{
    enemy->getShape().setPosition(
        -160.f,
        static_cast<float>(line * 50 + 5) // 8 horizontal rows for enemies
    );
    enemy->getShape().setSize(sf::Vector2f(this->enemyLength, 40.f));
    enemy->getShape().setFillColor(sf::Color::Yellow);
    enemy->getShape().setOutlineColor(sf::Color::Black);
    enemy->getShape().setOutlineThickness(1.f);
}

/**
 * @brief Initializes the player's properties like position, size, and colors.
 */
void Game::initPlayer()
{
    this->player.getShape().setPosition(5.f, 5.f);
    this->player.getShape().setSize(sf::Vector2f(40.f, 40.f));
    this->player.getShape().setFillColor(sf::Color::Red);
    this->player.getShape().setOutlineColor(sf::Color::Black);
    this->player.getShape().setOutlineThickness(1.f);
}

/**
 * @brief Loads and initializes the game font.
 *
 * Loads the font from a specific file. Displays an error message if loading fails.
 */
void Game::initFont()
{
    if (!this->font.loadFromFile("Valorax-lg25V.otf"))
    {
        std::cerr << "Error while loading font from ../fonts/Valorax-lg25V.otf";
    }
}

/**
 * @brief Initializes the score text properties like font, color, and size.
 */
void Game::initText()
{
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(20);
    this->text.setString("Score: " + std::to_string(this->score));
}

/**
 * @brief Checks if the game is running and not in an endgame state.
 *
 * @return True if the game window is still open and the game is not over, otherwise false.
 */
const bool Game::running() const
{
    return this->window->isOpen() && !this->endgame;
}


