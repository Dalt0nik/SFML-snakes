#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <Enemy.h>
#include <Player.h>

/**
 * @class Game
 * @brief Manages the overall game setup, loop, and termination.
 */
class Game {
public:
    /**
     * @brief Default constructor for the Game class.
     *
     * Initializes game components like window, fonts, text, and player.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     *
     * Cleans up dynamic resources by deleting the window object.
     */
    virtual ~Game();

    // Public Functions

    /**
     * @brief Handles all system events for the game.
     *
     * Polls for system events like window close and keyboard key presses.
     */
    void pollEvents();

    /**
     * @brief Updates the game state, player movement, and enemies.
     *
     * Manages events, input processing, player movement, and enemy updates.
     */
    void update();

    /**
     * @brief Updates enemies' movement and manages their lifecycle.
     *
     * Handles enemy spawning, movement, and removal.
     */
    void updateEnemies();

    /**
     * @brief Renders all game components onto the screen.
     *
     * Clears the screen, then draws all characters and score text.
     */
    void render();

    /**
     * @brief Renders all game characters onto the screen.
     *
     * Draws both the player and enemies onto the screen.
     */
    void renderCharacters();

    /**
     * @brief Renders the game score onto the specified render target.
     *
     * @param target The render target where the score will be drawn.
     */
    void renderScore(sf::RenderTarget* target);

    /**
     * @brief Spawns a new enemy in a random available line with a random speed.
     *
     * Uses an available line to create and initialize a new enemy.
     */
    void spawnEnemy();

    /**
     * @brief Checks if the game is running and not in an endgame state.
     *
     * @return True if the game window is still open and the game is not over.
     */
    const bool running() const;

private:
    // Variables

    // Window
    /**
     * @brief Pointer to the main game window.
     */
    sf::RenderWindow* window;

    /**
     * @brief Stores system events like keyboard and window events.
     */
    sf::Event ev;

    // Game Logic

    /**
     * @brief Flag indicating if the game is in an endgame state.
     */
    bool endgame;

    /**
     * @brief The current score of the game.
     */
    int score;

    /**
     * @brief Timer to keep track of enemy spawning intervals.
     */
    float enemySpawnTimer;

    /**
     * @brief Maximum time interval for enemy spawning.
     */
    float enemySpawnTimerMax;

    /**
     * @brief Maximum number of enemies allowed in the game.
     */
    int maxEnemies;

    /**
     * @brief The default length of each enemy.
     */
    float enemyLength;

    /**
     * @brief Flag indicating the player's movement direction.
     */
    bool goingUp;

    /**
     * @brief Flag indicating if the game is paused.
     */
    bool pause;

    /**
     * @brief The main font used for displaying text in the game.
     */
    sf::Font font;

    /**
     * @brief The main text object for displaying the game score.
     */
    sf::Text text;

    /**
     * @brief Vector that tracks which lines are available for enemy spawning.
     */
    std::vector<int> spawnlines;

    // Game Objects

    /**
     * @brief Vector holding all the enemies currently in the game.
     */
    std::vector<Enemy> enemies;

    /**
     * @brief The main player object.
     */
    Player player;

    // Private Functions

    /**
     * @brief Initializes default game variables.
     *
     * Sets up initial values for game variables like score, enemy spawn timers, etc.
     */
    void initVars();

    /**
     * @brief Initializes the main game window.
     *
     * Sets up the game window with a title and framerate limit.
     */
    void initWindow();

    /**
     * @brief Initializes the properties of an enemy based on a specific line.
     *
     * @param enemy Pointer to the Enemy object to initialize.
     * @param line The line number where the enemy will spawn.
     */
    void initEnemy(Enemy* enemy, int line);

    /**
     * @brief Initializes the player's properties like position, size, and colors.
     */
    void initPlayer();

    /**
     * @brief Loads and initializes the game font.
     *
     * Loads the font from a specific file.
     */
    void initFont();

    /**
     * @brief Initializes the score text properties like font, color, and size.
     */
    void initText();

    /**
     * @brief Updates the available lines for enemy spawning.
     *
     * Initializes a vector that tracks which lines are available for spawning.
     */
    void updateSpawnLines();

    /**
     * @brief Updates the game score text.
     *
     * Sets the game score text based on the current score.
     */
    void updateText();

    /**
     * @brief Processes user input for pausing and resuming the game.
     *
     * Monitors keyboard events to toggle game pause.
     */
    void updateInput();

    /**
     * @brief Serializes and hides all enemies by saving them to a file.
     *
     * Saves the current state of all enemies and clears the vector afterward.
     */
    void hideEnemies();

    /**
     * @brief Deserializes and shows all enemies from a file.
     *
     * Loads the enemies from a file and populates the vector with their state.
     */
    void showEnemies();

    /**
     * @brief Checks if the player and enemy collide.
     *
     * @param playerX The X-coordinate of the player.
     * @param enemyX The X-coordinate of the enemy.
     * @return True if the player and enemy collide.
     */
    bool isCollision(float playerX, float enemyX);
};
