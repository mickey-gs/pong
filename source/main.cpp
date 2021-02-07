#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"

void Draw(sf::RenderWindow* window, Paddle* paddles, Ball* ball) {
    window->clear(sf::Color::Black);
    sf::Font font;
    font.loadFromFile("./assets/atari.ttf");
    sf::Text text;
    for (int i = 0; i <= 1; i++) {
        window->draw(paddles[i].shape);
        window->draw(paddles[i].text);
    }
    window->draw(ball->shape);
    window->display();
}

void Input(sf::RenderWindow* window, Paddle* paddles) {
    static sf::Vector2u size = window->getSize();

    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::TextEntered:
                if (event.text.unicode == 81) {
                    window->close();
                }
                break;
            case sf::Event::Closed:
                window->close();
                break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        paddles[1].raise();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        paddles[1].lower(size);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        paddles[0].raise();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        paddles[0].lower(size);
    }

}

void Logic(sf::RenderWindow* window, Paddle* paddles, Ball* ball) {
    sf::FloatRect ballBox = ball->shape.getGlobalBounds();
    static unsigned int height = window->getSize().y;
    static unsigned int width = window->getSize().x;

    for (int i = 0; i <= 1; i++) {
        sf::FloatRect box = paddles[i].shape.getGlobalBounds();
        paddles[i].update();
        if (box.intersects(ballBox)) {
            ball->reflect(paddles[i]);
        }
    }

    if (ball->getPos().y < 0 || ball->getPos().y + 30.f > height) {
        ball->bounce();
    }

    if (ball->getPos().x < 0) {
        paddles[1].score();
        ball->reset();
    }
    
    if (ball->getPos().x + 30 > width) {
        paddles[0].score();
        ball->reset();
    }

    ball->update();
}

bool Prompt(sf::RenderWindow* window) {
        sf::Font font;
        font.loadFromFile("./assets/atari.ttf");
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(70);
        text.setFillColor(sf::Color::White);
        text.setString("GAME OVER");
        float middle_w = text.getGlobalBounds().width / 2;
        float middle_h = text.getGlobalBounds().height / 2;
        text.setOrigin(sf::Vector2f(middle_w, middle_h));
        text.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

        sf::Text text2;
        text2.setFont(font);
        text2.setFillColor(sf::Color::White);
        text2.setCharacterSize(30);
        text2.setString("Play again? (y/n)");
        middle_w = text2.getGlobalBounds().width / 2;
        float bottom = text2.getGlobalBounds().height;
        text2.setOrigin(sf::Vector2f(middle_w, bottom));
        text2.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y - bottom));

        bool waiting;
        while (waiting) {
            sf::Event event;
            while (window->pollEvent(event)) {

                if (event.type == sf::Event::TextEntered) {
                    switch (event.text.unicode) {
                        case 81:
                            window->close();
                            waiting = false;
                            return false;
                            
                        case 121:
                            waiting = false;
                            return true;

                        case 110:
                            waiting = false;
                            return false;
                    }
                }
            }

            window->draw(text);
            window->draw(text2);
            window->display();
        }
        return false;
}

void Splash(sf::RenderWindow* window) {
    sf::Time period = sf::seconds(0.042);

    for (int i = 0; i < 72; i++) {
        if (i < 12) {
            window->clear(sf::Color::Black);
        }
        else if (i < 24) {
            window->clear(sf::Color(31,31,31));
        }
        else if (i < 36) {
            window->clear(sf::Color(63,63,63));
        }
        else if (i < 48) {
            window->clear(sf::Color(127, 127, 127));
        }
        else if (i < 60) {
            window->clear(sf::Color(159,159,159));
        }
        else if (i < 72) {
            window->clear(sf::Color::White);
        }
        window->display();
        sleep(period);
    }

    sf::Font font;
    sf::Text text;
    font.loadFromFile("./assets/atari.ttf");
    text.setFont(font);
    text.setString("PONG");
    text.setCharacterSize(150);
    sf::FloatRect textBox = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textBox.left + textBox.width / 2, textBox.top + textBox.height / 2));
    text.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

    for (int i = 0; i < 96; i++) {
        if (i < 6) {
            text.setFillColor(sf::Color(255, 0, 0));
        }
        else if (i < 12) {
            text.setFillColor(sf::Color(255, 128, 0));
        }
        else if (i < 24) {
            text.setFillColor(sf::Color(255, 255, 0));
        }
        else if (i < 36) {
            text.setFillColor(sf::Color(0, 255, 0));
        }
        else if (i < 48) {
            text.setFillColor(sf::Color(0, 255, 255));
        }
        else if (i < 60) {
            text.setFillColor(sf::Color(0, 128, 255));
        }
        else if (i < 72) {
            text.setFillColor(sf::Color(0, 0, 255));
        }
        else if (i < 84) {
            text.setFillColor(sf::Color(0, 0, 128));
        }
        else if (i < 96) {
            text.setFillColor(sf::Color(0, 0, 0));
        }
        window->draw(text);
        window->display();
        sleep(period);
    }

    sf::Text prompt;
    prompt.setFont(font);
    prompt.setFillColor(sf::Color::Black);
    prompt.setString("Press space to begin!");
    prompt.setCharacterSize(30);
    textBox = prompt.getLocalBounds();
    prompt.setOrigin(sf::Vector2f(textBox.left + textBox.width / 2, textBox.top + textBox.height / 2));
    prompt.setPosition(sf::Vector2f(window->getSize().x / 2, (window->getSize().y / 2) + 3 * textBox.height));
    
    sf::Event event;
    while (true) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::TextEntered && event.text.unicode == 32) {
                window->clear(sf::Color::Black);
                window->display();
                return;
            }
        }
        window->draw(prompt);
        window->display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(930, 700), "Hello, world!");
    window.setFramerateLimit(60);

    Paddle pad_one;
    Paddle pad_two(930.f, 0.f);
    pad_two.setOrigin(sf::Vector2f(30.f, 0.f));
    pad_two.setPos(sf::Vector2f(930.f, 0.f));
    Paddle paddles[] = { pad_one, pad_two };

    Ball ball;

    Splash(&window);

    while (window.isOpen()) {
        while (window.isOpen() && paddles[0].getGoals() < 10 && paddles[1].getGoals() < 10) {
            Draw(&window, paddles, &ball);
            Input(&window, paddles);
            Logic(&window, paddles, &ball);
        }
        if (window.isOpen() && Prompt(&window)) {
            paddles[0].reset();
            paddles[1].reset();
            continue;
        }
        else {
            break;
        }
        window.close();
    }
    std::cout << "Thank you for playing!" << std::endl;
}
