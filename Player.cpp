#include "Player.h"

Player::Player(sf::VideoMode videoMode, sf::Vector2f dimensions)
{
    this->size.x = dimensions.x;
    this->size.y = dimensions.y;
    this->speed = 8;
    this->shape.setSize(this->size);
    this->shape.setFillColor(sf::Color::Cyan);
    this->shape.setOrigin(this->size.x * 0.5, this->size.y * 0.5);
    this->shape.setPosition(videoMode.width * 0.5, videoMode.height - 100);

}

Player::~Player()
{
    //dtor
}


sf::RectangleShape Player::getShape(){
    return this->shape;
}


void Player::moveRight(){
    this->shape.move(speed, 0);
}


void Player::moveLeft(){
    this->shape.move(-speed, 0);
}


sf::Vector2f Player::getSize(){
    return this->size;
}




