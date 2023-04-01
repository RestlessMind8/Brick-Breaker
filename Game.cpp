#include "Game.h"

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->newGame();
}


Game::~Game()
{
    delete this->window;
}


void Game::render(){
    this->window->clear(sf::Color(0, 0, 0));
    this->renderText(*this->window);
    this->renderPlayer(*this->window);
    this->renderBall(*this->window);
    this->renderBlocks(*this->window);
    this->window->display();
}


void Game::update(){
    this->pollEvents();
    //this->updateMousePosition();
    this->updateBallPosition();
    this->updateText();
    this->play();
}


void Game::pollEvents(){
    while(this->window->pollEvent(this->ev)){
        switch(this->ev.type){
            case sf::Event::Closed:
                this->window->close();
                break;
        }
    }
}


void Game::initVariables(){
    this->videoMode.height = 600;
    this->videoMode.width = 505;
    this->endGame = false;
    this->mouseHeld = false;
    this->clock = sf::Clock();
}


void Game::initWindow(){
    this->window = new sf::RenderWindow(this->videoMode, "Brick Breaker", sf::Style::Close);
    this->window->setFramerateLimit(60);
}


void Game::initFonts(){
    if(!this->font.loadFromFile("fonts/ARCADECLASSIC.ttf")){
        std::cout << "ERROR::GAME::INIFONTS::Failed to load font!" << "\n";
    }
}


void Game::updateMousePosition(){
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}


const bool Game::getEndGame() const{
    return this->endGame;
}


const bool Game::running() const{
    return this->window->isOpen();
}

void Game::initText(){
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(25);
    this->text.setPosition(0, 0);
}


void Game::updateText(){
    std::stringstream ss;
    ss.str("");
    ss << "Lives " << this->lives;
    this->text.setString(ss.str());
}


void Game::renderPlayer(sf::RenderTarget &target){
    target.draw(this->player->getShape());
}


void Game::renderBall(sf::RenderTarget &target){
    target.draw(this->ball->getShape());
}


void Game::renderBlocks(sf::RenderTarget &target){
    for(int i = 0; i < this->blocks.size(); i++){
        target.draw(this->blocks[i].getShape());
    }
}

void Game::renderText(sf::RenderTarget &target){
    target.draw(this->text);
}


void Game::newGame(){
    this->playerDimensions.x = 70.f;
    this->playerDimensions.y = 8.f;
    this->player = new Player(this->videoMode, this->playerDimensions);
    this->ballRadius = 5.f;
    this->ball = new Ball(this->videoMode, this->ballRadius);
    this->lives = 3;
    this->setBlocks();
    this->initText();
}


void Game::play(){
    if(this->ev.type == sf::Event::KeyPressed){
        switch(this->ev.key.code){
            case sf::Keyboard::Right:
                if(checkPlayerBounds() != 1){
                    this->player->moveRight();
                }
                break;
            case sf::Keyboard::Left:
                if(checkPlayerBounds() != -1){
                    this->player->moveLeft();
                }
                break;
            default:
                break;
        }
    }
}


int Game::checkPlayerBounds(){
    sf::Vector2f playerPosition = this->player->getShape().getPosition();
    int playerSize = this->player->getSize().x;
    if((playerPosition.x + playerSize * 0.5) > this->videoMode.width)
        return 1;
    else if(((playerPosition.x - playerSize * 0.5) < 0))
        return -1;
    else return 0;
}


void Game::setBlocks(){
    sf::Vector2f blockPosition;
    sf::Vector2f blockSize;
    blockSize.x = 45.f;
    blockSize.y = 20.f;
    blockPosition.x = 5.f;
    blockPosition.y = 50.f + blockSize.y;
    for(int j = 0; j < 10; j++){
        for(int i = 0; i < 6; i++){
            this->blocks.push_back(Block(blockSize, blockPosition));
            blockPosition.y +=  blockSize.y + 5.f;
        }
        blockPosition.y = 50.f + blockSize.y;
        blockPosition.x += blockSize.x + 5.f;
    }
}


void Game::updateBallPosition(){
    switch(ballCollider()){
        case 1:
            this->ball->setXDirection(-this->ball->getDirections().x);
        break;
        case 2:
            this->ball->setYDirection(-this->ball->getDirections().y);
        break;
        case 3:
            this->ball->setYDirection(-1);
            this->ball->setXDirection(-1);
        break;
        case 4:
            this->ball->setYDirection(-1);
            this->ball->setXDirection(1);
        break;
    }
    this->ball->move();
}


int Game::ballCollider(){
    const sf::Vector2f ballPosition = this->ball->getShape().getPosition();
    const sf::Vector2f playerPosition = this->player->getShape().getPosition();
    int blockCollisionValue = this->checkBlockCollision();

    if((ballPosition.x + ballRadius) > this->videoMode.width
       || (ballPosition.x - ballRadius) < 0
       || blockCollisionValue == 1){
        return 1;
    }else if((ballPosition.y + ballRadius) > this->videoMode.height
             || (ballPosition.y - ballRadius) < 0
             || blockCollisionValue == 2){
                 if(blockCollisionValue != 2){
                    this->lives -= 1;
                 }
        return 2;
    }else if((ballPosition.y + ballRadius) > (playerPosition.y - playerDimensions.y)
             && (ballPosition.y - ballRadius) < (playerPosition.y + playerDimensions.y)
             && (ballPosition.x + ballRadius > (playerPosition.x - playerDimensions.x * 0.5))
             && (ballPosition.x - ballRadius < (playerPosition.x))
             || blockCollisionValue == 3){
        return 3;
    }else if((ballPosition.y + ballRadius) > (playerPosition.y - playerDimensions.y)
             && (ballPosition.y - ballRadius) < (playerPosition.y + playerDimensions.y)
             && (ballPosition.x + ballRadius > (playerPosition.x))
             && (ballPosition.x - ballRadius < (playerPosition.x + playerDimensions.x * 0.5))){
        return 4;
    }
}


float Game::clamp(float value, float minn, float maxx){
    /**
        @return float
        A function that limits value to the range minn..maxx
    */
    if(value < minn) return minn;
    else if(value > maxx) return maxx;
    else return value;
}


int Game::checkBlockCollision(){
    /**
        @return int
        A int function that takes in a rectangle and a circle and returns:
        3 if they hit at a corner
        2 if they hit on the top or bottom
        1 if they hit on the left or right
        0 if they don't hit
        Make sure circle origin is set to center
    */
    sf::CircleShape c = this->ball->getShape();
    int value = 0;
    if(this->ball->getPosition().y < this->videoMode.height * 0.5){
        for(int i = 0; i < this->blocks.size(); i++){
            sf::RectangleShape r = this->blocks.at(i).getShape();
            //find the closest point to the circle within the rectangle
            float closestX = clamp(c.getPosition().x, r.getPosition().x, r.getPosition().x + r.getSize().x);
            float closestY = clamp(c.getPosition().y, r.getPosition().y, r.getPosition().y + r.getSize().y);

            //calculate the distance between the circle's center and this closest point
            float distanceX = c.getPosition().x - closestX;
            float distanceY = c.getPosition().y - closestY;

            //if the distance is less than the circle's radius, an intersection occurs
            float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
            if(distanceSquared < c.getRadius()*c.getRadius() && closestX != c.getPosition().x && closestY != c.getPosition().y){
                value = 3;
            }else if(distanceSquared < c.getRadius()*c.getRadius() && closestX == c.getPosition().x){
                value = 2;
            }else if(distanceSquared < c.getRadius()*c.getRadius() && closestY == c.getPosition().y){
                value = 1;
            }
            //erase block and return value
            if(value){
                this->blocks.erase(this->blocks.begin() + i);
                return value;
            }
        }
    }
    return 0;
}


















