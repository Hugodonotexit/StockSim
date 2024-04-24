#include <iostream>
#include "game.h"

using namespace sf;

int main() {
    //Init Game front end
    Game stockSim;

    //Game loop
    while (stockSim.getWinIsOpen())
    {
        //Update
        stockSim.update();
        //Render
        stockSim.render();
    }
    

    return 0;
}