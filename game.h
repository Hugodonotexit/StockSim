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
#include "asset/events.h"
#include "function/gametime.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace sf;

class Game
{
private:
    //Window
    RenderWindow *window = nullptr;
    VideoMode videoMode;
    Event keyEvent;

    //Mouse position
    Vector2i mousePosWin;

    //Var
    Asset** cryptos = nullptr;
    //Asset** forexs = nullptr;
    Asset** stocks = nullptr;
    Events** events = nullptr;
    Gametime gametime;
    int numStocks;
    int numCryptos;
    int numEvents;
    //int numForexs;

    //Objects
    

    //Functions
    void initWin();
    void initAsset();
    void initEvents();

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