#include "Ball.h"

Ball::Ball(sf::VideoMode videoMode, float radius)
{
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setPosition(videoMode.width * 0.5, videoMode.height - 120);
    this->shape.setOrigin(5, 5);
    this->xDirection = 1;
    this->yDirection = 1;
    this->speed = 5;
}

Ball::~Ball()
{
    //dtor
}


sf::CircleShape Ball::getShape(){
    return shape;
}


void Ball::move(){
    this->shape.move(xDirection * speed, yDirection * speed);
}


void Ball::setXDirection(int direction){
    this->xDirection = direction;
}


void Ball::setYDirection(int direction){
    this->yDirection = direction;
}
