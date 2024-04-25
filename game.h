//Game engine
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include "asset/asset.h"
#include "asset/crypto.h"
#include "asset/forex.h"
#include "asset/stock.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace sf;

class Game
{
private:
    //Window
    RenderWindow *window;
    VideoMode videoMode;
    Event keyEvent;

    //Mouse position
    Vector2i mousePosWin;

    //Var
    double randSeed;
    Asset** cryptos;
    Asset** forexs;
    Asset** stocks;


    //Objects
    

    //Functions
    void initVar();
    void initWin();
    void initAsset();

public:
    Game();
    ~Game();

    //Functions
    const bool getWinIsOpen();
    void mousePosUpdate();
    void eventUpdate(); //check keys input
    void update();
    void render();
};


#endif