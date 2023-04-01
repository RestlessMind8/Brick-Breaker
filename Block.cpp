#include "Block.h"

Block::Block(sf::Vector2f dimensions, sf::Vector2f position)
{
    this->size.x = dimensions.x;
    this->size.y = dimensions.y;
    this->shape.setSize(this->size);
    this->shape.setFillColor(sf::Color::White);
    //this->shape.setOrigin(this->size.x * 0.5, this->size.y * 0.5);
    this->shape.setPosition(position.x, position.y);

}

Block::~Block()
{
    //dtor
}



sf::RectangleShape Block::getShape(){
    return this->shape;
}


sf::Vector2f Block::getPosition(){
    return this->shape.getPosition();
}


sf::Vector2f Block::getSize(){
    return this->size;
}


