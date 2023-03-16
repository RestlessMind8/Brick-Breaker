#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Ball.h"


class Game
{
    public:
        Game();
        virtual ~Game();
    public:
        void update();
        void render();
        const bool running() const;
        const bool getEndGame() const;

    protected:

    private:
        sf::RenderWindow *window;
        sf::Event ev;
        sf::VideoMode videoMode;
        sf::Clock clock;
        sf::Font font;
        sf::Text text;
        Player *player;
        Ball *ball;
        sf::Vector2f playerDimensions;
        float ballRadius;

        //mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //game logic
        bool endGame;
        bool mouseHeld;
        bool started;
        float score;

        //private functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void pollEvents();
        void updateMousePosition();
        void renderText();
        void renderPlayer(sf::RenderTarget &target);
        void renderBall(sf::RenderTarget &target);
        void play();
        int checkPlayerBounds();
        void updateBallPosition();
        int ballCollider();


};

#endif // GAME_H












