#include <string>
#include <SFML/Graphics.hpp>
#ifndef GUARD_paddle_h
#define GUARD_paddle_h

class Paddle {
    public:
        Paddle();
        Paddle(float x, float y);
        sf::RectangleShape shape;
        void raise();
        void lower();
        void lower(sf::Vector2u size);
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

#endif
