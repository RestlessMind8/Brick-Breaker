#include "Ball.h"

Ball::Ball(sf::VideoMode videoMode, float radius)
{
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setPosition(videoMode.width * 0.5, videoMode.height - 120);
    this->shape.setOrigin(5, 5);
    this->directions.x = -1;
    this->directions.y = 1;
    this->speed = 5;
}

Ball::~Ball()
{
    //dtor
}


sf::CircleShape Ball::getShape(){
    return shape;
}


sf::Vector2f Ball::getPosition(){
    return this->shape.getPosition();
}


void Ball::move(){
    this->shape.move(this->directions.x * speed, this->directions.y * speed);
}


void Ball::setXDirection(int direction){
    this->directions.x = direction;
}


void Ball::setYDirection(int direction){
    this->directions.y = direction;
}


sf::Vector2i Ball::getDirections(){
    return this->directions;
}









