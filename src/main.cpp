#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

#include "../Include/Game.h"


int main()
{	
    // Init Srand
    std::srand(static_cast<unsigned>(time(NULL)));

    
    Game game;

    //game loop
    while (game.running())
    {
        //Update
        game.update();

        //Render
        game.render();

    }


    //End of the Game

    return 0;
}