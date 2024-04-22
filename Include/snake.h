#include <memory>
#pragma once

class Snake {
public:
    Snake(float initialDirection, float initialSpeed, float initialX, float initialY);
    Snake(const Snake& other);
    Snake& operator=(const Snake& other);
    ~Snake();
    void move();
    void display();
    void display_file(std::ofstream* outFile);
    static int getLiveCount();
    double getX();
    double getY();
    void turn(int degrees);
    void teleport(double x, double y);

private:
    class SnakeImpl;
    std::unique_ptr<SnakeImpl> pImpl;
};
