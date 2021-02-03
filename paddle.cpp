#include <iostream>
#include <SFML/Graphics.hpp>

class Paddle {
    public:
        Paddle();
        Paddle(float width, float height);
        sf::RectangleShape shape;
        void raise();
        void lower();
    private:
        sf::Vector2f size;
        float x, y;
        sf::Vector2f pos;
};

Paddle::Paddle(): size(30.f, 200.f), shape(size), x(0), y(0), pos(x, y) {
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color::White);
}

Paddle::Paddle(float width, float height): size(width, height), shape(size), pos(x, y) {
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color::White);
}

void Paddle::raise() {
    if (pos.y > 0) {
        pos.y -= 6.f;
        shape.setPosition(pos);
        std::cout << pos.y << std::endl;
    }
}

void Paddle::lower() {
    pos.y += 50.f;
    shape.setPosition(pos);
    std::cout << pos.y << std::endl;
}
