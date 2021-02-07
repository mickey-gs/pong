#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Paddle {
    public:
        Paddle();
        Paddle(float x, float y);
        sf::RectangleShape shape;
        void raise();
        void lower();
        void lower(sf::Vector2u);
        void score();
        int getGoals();

        void setOrigin(sf::Vector2f origin);
        void setPos(sf::Vector2f position);

        float speed();
        void update();
        void reset();

        sf::Text text;
    private:
        sf::Vector2f origin;
        sf::Vector2f size;
        float x, y;
        sf::Vector2f pos;
        float lastHeight;
        int goals;
};

Paddle::Paddle() {
    x = 0.f;
    y = 0.f;
    goals = 0;
    pos = sf::Vector2f(x, y);
    origin = sf::Vector2f(x, y);
    size = sf::Vector2f(30.f, 200.f);
    shape = sf::RectangleShape(size);
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color::White);

    sf::Font font;
    font.loadFromFile("./assets/atari.ttf");
    text = sf::Text();
    text.setFont(font);
    text.setCharacterSize(45);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x + 120.f, 10.f));
    text.setString(std::to_string(goals));
}

Paddle::Paddle(float x, float y) {
    goals = 0;
    pos = sf::Vector2f(x, y);
    origin = sf::Vector2f(x + 30.f, y);
    size = sf::Vector2f(30.f, 200.f);
    shape = sf::RectangleShape(size);
    shape.setPosition(sf::Vector2f(0.f, 0.f));
    shape.setFillColor(sf::Color::White);

    sf::Font font;
    font.loadFromFile("./assets/atari.ttf");
    text = sf::Text();
    text.setFont(font);
    text.setCharacterSize(45);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x - 170.f, 10.f));
    text.setString(std::to_string(goals));
}

void Paddle::raise() {
    if (pos.y > 0) {
        pos.y -= 12.f;
        shape.setPosition(pos);
    }
}

void Paddle::lower() {
    pos.y += 12.f;
    shape.setPosition(pos);
}
        
void Paddle::lower(sf::Vector2u size) {
    if (pos.y + this->size.y < size.y) {
        pos.y += 12.f;
        shape.setPosition(pos);
    }
}
        
void Paddle::setOrigin(sf::Vector2f origin) {
    this->shape.setOrigin(origin);
}

void Paddle::setPos(sf::Vector2f position) {
    pos = position;
    this->shape.setPosition(pos);
}

float Paddle::speed() {
    return (pos.y - lastHeight) / 0.0166667;
}

void Paddle::update() {
    lastHeight = pos.y;
}

void Paddle::score() {
    ++goals;
    text.setString(std::to_string(goals));
}

int Paddle::getGoals() {
    return goals;
}

void Paddle::reset() {
    goals = 0;
    text.setString(std::to_string(goals));
}
