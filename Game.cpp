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
    this->window->display();
}


void Game::update(){
    this->pollEvents();
    this->updateMousePosition();
    //this->play();
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
