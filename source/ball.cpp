#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "paddle.h"

int crand(int n) {
    return rand() % n;
}

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

Ball::Ball() {
    shape = sf::RectangleShape(sf::Vector2f(30.f, 30.f));
    shape.setFillColor(sf::Color::White);
    pos = sf::Vector2f(435.f, 350.f);
    shape.setPosition(pos);
    vel = newSpeed();
}

void Ball::update() {
    pos.x += vel.x;
    pos.y += vel.y;
    shape.setPosition(pos);
}

void Ball::reflect(Paddle paddle) {
    sf::FloatRect obstacle = paddle.shape.getGlobalBounds();
    if (pos.x < 5.f || pos.x > 905.f) {
        vel.y = -vel.y;
    }
    else {
        vel.x = -vel.x;
        if (std::abs(vel.x) < 20.f) {
            vel.x += (vel.x < 0 ? -1.f : 1.f);
        }
        vel.y = calcAngle(vel.x, obstacle);
    }
}

double Ball::calcAngle(double vel_x, sf::FloatRect obstacle) {
    // cuts the paddle into 7 segments, calculates which segment the ball is in, then uses
    // the appropriate return angle.
    // the multiplier ensures the ball does not travel too fast vertically- using vel.x is much too fast
    double slice = obstacle.height / 7;
    double distance = pos.y - obstacle.top;
    double multiplier;
    multiplier = std::abs(vel.x) / 2;
 
    // (the ball can sometimes be above the top of the paddle)
    distance = (distance < 0.0 ? 0.0 : distance);

    if (distance < slice) {
        // ~45 degrees up
        return multiplier * std::tan(-3.1415 / 4);
    }
    else if (distance < slice * 2) {
        // ~30 degrees up
        return multiplier * std::tan(-0.5236);
    }
    else if (distance < slice * 3) {
        // ~15 degrees up
        return multiplier * std::tan(-0.2618);
    }
    else if (distance < slice * 4) {
        // 0 degrees
        return multiplier * std::tan(0);
    }
    else if (distance < slice * 5) {
        // ~15 degrees up
        return multiplier * std::tan(0.2618);
    }
    else if (distance < slice * 6) {
        // ~30 degrees down
        return multiplier * std::tan(0.5236);
    }
    else {
        // ~45 degrees up
        return multiplier * std::tan(3.1415 / 4);
    }
}

void Ball::bounce() {
    vel.y = -vel.y;
}

void Ball::reset() {
    pos = sf::Vector2f(435.f, 350.f);
    shape.setPosition(pos);
    vel = newSpeed();
}
        
sf::Vector2f Ball::getPos() {
    return pos;
}

sf::Vector2f Ball::newSpeed() {
    float x_vel = (crand(2) == 0 ? 10.f : -10.f);
    float y_vel = (crand(2) == 0 ? crand(5) + 1.f : -crand(5) - 1.f);
    return sf::Vector2f(x_vel, y_vel);
}
