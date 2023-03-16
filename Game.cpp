#include "Game.h"

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}


Game::~Game()
{
    delete this->window;
}


void Game::render(){
    this->window->clear(sf::Color(0, 0, 0));
    this->renderPlayer(*this->window);
    this->renderBall(*this->window);
    this->window->display();
}


void Game::update(){
    this->pollEvents();
    this->updateMousePosition();
    this->updateBallPosition();
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
    this->videoMode.width = 500;
    this->endGame = false;
    this->mouseHeld = false;
    this->clock = sf::Clock();
    this->playerDimensions.x = 70.f;
    this->playerDimensions.y = 8.f;
    this->player = new Player(this->videoMode, this->playerDimensions);
    this->ballRadius = 5.f;
    this->ball = new Ball(this->videoMode, this->ballRadius);
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
    this->text.setFillColor(sf::Color::Black);
}


void Game::renderPlayer(sf::RenderTarget &target){
    target.draw(this->player->getShape());
}


void Game::renderBall(sf::RenderTarget &target){
    target.draw(this->ball->getShape());
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


void Game::updateBallPosition(){
    switch(ballCollider()){
        case 1:
            this->ball->setXDirection(-1);
        break;
        case 2:
            this->ball->setXDirection(1);
        break;
        case 3:
            this->ball->setYDirection(-1);
        break;
        case 4:
            this->ball->setYDirection(1);
        break;
        case 5:
            this->ball->setYDirection(-1);
            this->ball->setXDirection(-1);
        break;
        case 6:
            this->ball->setYDirection(-1);
            this->ball->setXDirection(1);
        break;
    }
    this->ball->move();
}


int Game::ballCollider(){
    sf::Vector2f ballPosition = this->ball->getShape().getPosition();
    sf::Vector2f playerPosition = this->player->getShape().getPosition();

    if((ballPosition.x + ballRadius) > this->videoMode.width){
        return 1;
    }else if((ballPosition.x - ballRadius) < 0){
        return 2;
    }else if((ballPosition.y + ballRadius) > this->videoMode.height){
        return 3;
    }else if((ballPosition.y - ballRadius) < 0){
        return 4;
    }else if((ballPosition.y + ballRadius) > (playerPosition.y - playerDimensions.y)
             && (ballPosition.y - ballRadius) < (playerPosition.y + playerDimensions.y)
             && (ballPosition.x + ballRadius > (playerPosition.x - playerDimensions.x * 0.5))
             && (ballPosition.x - ballRadius < (playerPosition.x))){
        return 5;
    }else if((ballPosition.y + ballRadius) > (playerPosition.y - playerDimensions.y)
             && (ballPosition.y - ballRadius) < (playerPosition.y + playerDimensions.y)
             && (ballPosition.x + ballRadius > (playerPosition.x))
             && (ballPosition.x - ballRadius < (playerPosition.x + playerDimensions.x * 0.5))){
        return 6;
    }
}





