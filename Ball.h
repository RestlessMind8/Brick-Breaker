#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>

class Ball
{
    public:
        Ball(sf::VideoMode videoMode, float radius);
        virtual ~Ball();
    public:
        sf::CircleShape getShape();
        void move();
        void setXDirection(int direction);
        void setYDirection(int direction);
        sf::Vector2f getPosition();
        sf::Vector2i getDirections();

    protected:

    private:
        sf::CircleShape shape;
        sf::Vector2i directions;
        float speed;

};

#endif // BALL_H
