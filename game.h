//Game engine
#ifndef GAME_H
#define GAME_H

#define INFOTEXT_LINE 3

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include "asset/asset.h"
#include "asset/crypto.h"
#include "asset/stock.h"
#include "asset/cryptolizedStock.h"
#include "asset/events.h"
#include "function/gametime.h"
#include "function/player.h"
#include "function/graph.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip> 
#include <vector>
#include <thread>

using namespace sf;

class Game
{
private:
    //Window
    RenderWindow *window = nullptr;
    Sprite *sprite = nullptr;
    Sprite *sprite1 = nullptr;
    VideoMode videoMode;
    Event keyEvent;
    RenderTexture *boxInfoContainer = nullptr;
    RenderTexture *graphContainer = nullptr;
    RectangleShape boxInfo, boxGraph;
    Font openSans;
    Font pixeBoy;
    Text infoText[INFOTEXT_LINE];
    Text timeChange[TIMECHANGE_MODE];
    View view;

;
    //Mouse position
    Vector2i mousePosWin;
    Vector2f mousePosView;

    //Class
    Asset** cryptos = nullptr;
    Asset** stocks = nullptr;
    Asset** cryptolizedStock = nullptr;
    Events** events = nullptr;
    Asset* openedAsset = nullptr;
    Gametime gametime;
    Player player;

    //Var
    int numStocks, numCryptos, numCryptolizedStock ,numEvents;
    int timeScaleIndex = 1;
    int oldTime = 0;
    double dragOldPostion;
    bool dragging;
    //int numForexs;

    //Objects

    //Functions
    void initWin();
    void initBox();
    void updateAsset(Asset*);
    void updateText();
    void renderText(RenderTarget&);
    void renderGraph(RenderTarget&);
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