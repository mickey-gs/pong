#include <chrono>
#include <SFML/Graphics.hpp>
#include "paddle.h"

class Ball {
    public:
        Ball();
        sf::RectangleShape shape;
        void update();
        void reflect(Paddle paddle);
        void bounce();
        void reset();
        sf::Vector2f getPos();
    private:
        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::Vector2f newSpeed();
        double calcAngle(double vel_x, sf::FloatRect obstacle);
};
