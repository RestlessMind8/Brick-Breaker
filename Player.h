#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player(sf::VideoMode videoMode);
        virtual ~Player();

    public:
        sf::RectangleShape getShape();
        void moveRight();
        void moveLeft();
        sf::Vector2f getSize();

    protected:

    private:
        sf::RectangleShape shape;
        sf::Vector2f size;
        int speed;

        bool checkBounds();
};

#endif // PLAYER_H
