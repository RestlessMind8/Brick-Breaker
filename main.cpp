#include <iostream>
#include "Game.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    Game game;

    while (game.running() && !game.getEndGame()) //loop
    {
        //Render
        game.render();

        //Update
        game.update();
    }

    return 0;
}
