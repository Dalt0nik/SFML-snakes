#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

#include "../Include/Game.h"

/**
 * @file
 * @brief Contains the main function that initializes and runs the game loop.
 */

 /**
  * @brief Main entry point for the game application.
  *
  * Initializes the game by setting up the random seed, creates a `Game` object, and executes the game loop until the game ends.
  *
  * - **Game Initialization**: Sets up the random number generator.
  * - **Game Loop**: Repeatedly updates and renders the game while it is running.
  *
  */
int main() {
    // Initialize random seed
    std::srand(static_cast<unsigned>(time(NULL)));

    // Create the Game object
    Game game;

    // Game loop
    while (game.running()) {
        // Update game state
        game.update();

        // Render the game frame
        game.render();
    }

    // End of the game
    return 0;
}
