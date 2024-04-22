#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>

//#include "../include/snake.h"
//#include "../include/GameBorderException.h"




//void writeToFile(std::ofstream* outFile, const std::string& text) {
//    if (outFile->is_open()) {
//        *outFile << text;
//    } else {
//        std::cerr << "Unable to open file while writing\n";
//    }
//}

int main()
{	
    //window setup
    sf::RenderWindow window(sf::VideoMode(480, 480), "Snakes", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    //game loop
    while (window.isOpen())
    {
        //events
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (ev.key.code == sf::Keyboard::Escape)
                    {
                        window.close();
                    }
                    break;
            }

        }

        //Update


        //Render
        window.clear(); //clear old frame

        //Drawing


        window.display(); //display newly created frame

    }


    //End of the Game





    //srand(time(NULL));

    //std::ofstream outFile("log.txt");

    //// Dynamically allocate the original snake
    //Snake* originalSnake = new Snake(90, 2.5, 0.0, 0.0);

    //std::cout << "Original snake:\n";
    //writeToFile(&outFile, "Original snake:\n");
    //originalSnake->display();
    //originalSnake->display_file(&outFile);

    //// clone the original snake using the copy constructor
    //Snake* clonedSnake = new Snake(*originalSnake);

    //std::cout << "Cloned snake:\n";
    //writeToFile(&outFile, "Cloned snake:\n");
    //clonedSnake->display();
    //clonedSnake->display_file(&outFile);


    //// Move and display the original snake
    //try
    //{
    //    std::cout << "trying to move original:\n";
    //    writeToFile(&outFile, "trying to move original:\n");
    //    originalSnake->move();
    //}
    //catch(const GameBorderException& e)
    //{
    //    std::cerr << "Error: " << e.what() << std::endl;
    //    writeToFile(&outFile, "Error: " + std::string(e.what()) + "\n");
    //    double x = originalSnake->getX();
    //    double y = originalSnake->getY();

    //    originalSnake->teleport(x, y);

    //    std::cout << "Got teleported: \n";
    //    writeToFile(&outFile, "Got teleported: \n");
    //}
    //
    //originalSnake->display();
    //originalSnake->display_file(&outFile);

    //std::cout << "Cloned snake still there:\n";
    //writeToFile(&outFile, "Cloned snake still there:\n");
    //clonedSnake->turn(135);
    //clonedSnake->display();
    //clonedSnake->display_file(&outFile);

    //
    //std::cout << "Cloned snake turned 135 degrees:\n";
    //writeToFile(&outFile, "Cloned snake turned 135 degrees:\n");

    //try
    //{
    //    std::cout << "trying to move cloned:\n";
    //    writeToFile(&outFile, "trying to move cloned:\n");
    //    clonedSnake->move();
    //}
    //catch(const GameBorderException& e)
    //{
    //    std::cerr << "Error: " << e.what() << std::endl;
    //    writeToFile(&outFile, "Error: " + std::string(e.what()) + "\n");
    //    double x = clonedSnake->getX();
    //    double y = clonedSnake->getY();

    //    clonedSnake->teleport(x, y);

    //    std::cout << "Got teleported: \n";
    //    writeToFile(&outFile, "Got teleported: \n");
    //}
    //clonedSnake->display();
    //clonedSnake->display_file(&outFile);


    //std::cout << "Snake live count: " << Snake::getLiveCount() << std::endl;
    //writeToFile(&outFile, "Snake live count: " + std::to_string(Snake::getLiveCount()) + "\n");

    //delete originalSnake;
    //
    //std::cout << "Snake live count: " << Snake::getLiveCount() << std::endl;
    //writeToFile(&outFile, "Snake live count: " + std::to_string(Snake::getLiveCount()) + "\n");

    return 0;
}