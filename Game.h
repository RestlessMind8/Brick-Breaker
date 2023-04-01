#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Ball.h"
#include <vector>
#include "Block.h"
#include <stdlib.h>
#include <sstream>

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
        std::vector<Block> blocks;

        //mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //game logic
        bool endGame;
        bool mouseHeld;
        bool started;
        float score;
        int lives;

        //private functions
        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void newGame();
        void pollEvents();
        void updateMousePosition();
        void updateText();
        void renderText(sf::RenderTarget &target);
        void renderPlayer(sf::RenderTarget &target);
        void renderBall(sf::RenderTarget &target);
        void play();
        int checkPlayerBounds();
        void updateBallPosition();
        int ballCollider();
        void setBlocks();
        void renderBlocks(sf::RenderTarget &target);
        int checkBlockCollision();
        float clamp(float value, float minn, float maxx);
        void playerDies();
        void gameOver();

};

#endif // GAME_H












