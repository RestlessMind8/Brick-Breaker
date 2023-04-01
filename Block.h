#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>

class Block
{
    public:
        Block(sf::Vector2f dimensions, sf::Vector2f position);
        virtual ~Block();

    public:
        sf::RectangleShape getShape();
        sf::Vector2f getPosition();
        sf::Vector2f getSize();

    protected:

    private:
        sf::RectangleShape shape;
        sf::Vector2f size;
};

#endif // BLOCK_H
