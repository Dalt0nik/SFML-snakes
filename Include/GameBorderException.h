#ifndef GAME_BORDER_EXCEPTION_H
#define GAME_BORDER_EXCEPTION_H

#include <exception>

class GameBorderException : public std::exception {
public:
    const char* what() const throw() {
        return "Snake has moved out of the game border!";
    }
};

#endif // GAME_BORDER_EXCEPTION_H