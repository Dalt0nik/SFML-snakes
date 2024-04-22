#include "snake.h"
#include "GameBorderException.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>


#define M_PI 3.14159265358979323846
#define BORDER_WIDTH 100
#define BORDER_HEIGHT 50


class Snake::SnakeImpl {
public:
    SnakeImpl(float initialDirection, float initialSpeed, float initialX, float initialY)
        : direction(initialDirection), speed(initialSpeed), x(initialX), y(initialY) {
        this->id = rand() % 1000 + 1;
        liveCount++;
    }
    SnakeImpl(const SnakeImpl& other);

    ~SnakeImpl() {
        liveCount--;
    }

    void move() {
        float radians = float(direction) * M_PI / 180;
        x += round(speed * std::cos(radians) * 10) / 10;
        y += round(speed * std::sin(radians) * 10) / 10;
        std::cout << x << " " << y << std::endl;
        if (x < 0 || x > BORDER_WIDTH || y < 0 || y > BORDER_HEIGHT) {
            throw GameBorderException();
        }
        std::cout << "Snake " << id << " moved to position (" << x << ", " << y << ")" << std::endl;
    }

    void display() {
        std::cout << "Snake ID: " << id << ", Direction: " << direction << ", Speed: " << speed
                  << ", Position: (" << x << ", " << y << ")" << std::endl;
    }

    void display_file(std::ofstream* outFile) {
        if (outFile->is_open()) {
            *outFile << "Snake ID: " << id << ", Direction: " << direction << ", Speed: " << speed
                      << ", Position: (" << x << ", " << y << ")" << std::endl;
        } else {
            std::cerr << "Unable to open file in dislpay\n";
        }
    }

    static int getLiveCount() {
        return liveCount;
    }

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

    void turn(int degrees) {
        direction += degrees;
        direction %= 360;
    }

    void teleport(double x, double y){
        this->x = fabs(x);
        this->y = fabs(y);
    }

private:
    int id;
    static int liveCount;
    int direction;
    float speed;
    float x, y;
};

int Snake::SnakeImpl::liveCount = 0;


Snake::Snake(float initialDirection, float initialSpeed, float initialX, float initialY)
    : pImpl(new SnakeImpl(initialDirection, initialSpeed, initialX, initialY)) {}

Snake::~Snake() = default;

void Snake::move() {
    pImpl->move();
}

void Snake::display() {
    pImpl->display();
}

void Snake::display_file(std::ofstream* outFile) {
    pImpl->display_file(outFile);
}

int Snake::getLiveCount() {
    return SnakeImpl::getLiveCount();
}

double Snake::getX() {
    return pImpl->getX();
}

double Snake::getY() {
    return pImpl->getY();
}

void Snake::turn(int degrees) {
    pImpl->turn(degrees);
}

void Snake::teleport(double x, double y){
    pImpl->teleport(x, y);
}


Snake::Snake(const Snake& other)
    : pImpl(new SnakeImpl(*other.pImpl))
{
}

Snake& Snake::operator=(const Snake& other)
{
    if (this != &other) {
        pImpl = std::make_unique<SnakeImpl>(*other.pImpl);
    }
    return *this;
}

Snake::SnakeImpl::SnakeImpl(const SnakeImpl& other)
    : direction(other.direction), speed(other.speed), x(other.x), y(other.y), id(other.id)
{
    liveCount++;
}
