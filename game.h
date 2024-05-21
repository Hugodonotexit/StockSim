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
#include "function/portfolio.h"
#include "function/graph.h"
#include "layout/list.h"
#include "layout/listItem.h"
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
    Sprite *sprite2 = nullptr;
    Sprite *sprite3 = nullptr;
    VideoMode videoMode;
    Event keyEvent;
    RenderTexture *boxInfoContainer = nullptr;
    RenderTexture *graphContainer = nullptr;
    RenderTexture *listContainer = nullptr;
    RenderTexture *newContainer = nullptr;
    RenderTexture *actionContainer = nullptr;
    RenderTexture *portfolioContainer = nullptr;
    RectangleShape boxInfo, boxGraph, boxAssetInfo, boxList,boxListTab[3];
    RectangleShape ButtonBuy, ButtonSell, ButtonAdd, ButtonMinus;
    Font openSans;
    Font pixeBoy;
    Text EvenText;
    Text infoText[INFOTEXT_LINE];
    Text timeChange[TIMECHANGE_MODE];
    Text typeTab[TAB_NUM]; 
    
    //Mouse position
    Vector2i mousePosWin;
    Vector2f mousePosView;

    //Class
    randomGen rnd;
    Asset** cryptos = nullptr;
    Asset** stocks = nullptr;
    Asset** cryptolizedStock = nullptr;
    Asset* openedAsset = nullptr;
    List** list = nullptr;
    Events** events = nullptr;
    Gametime gametime;
    Player player;

    //Var
    int numStocks = 0, numCryptos = 0, numCryptolizedStock = 0,numEvents = 0;
    int timeScaleIndex = 1, listIndex = 0;
    int oldTime = 0;
    double dragOldPostion;
    bool dragging, isEvent = false;
    //int numForexs;

    //Objects

    //Functions
    void initWin();
    void initBox();
    void updateAsset(bool, Events*);
    Events *updateEvent();
    void updateText();
    void updateListItemText();
    void renderInfoText(RenderTarget&);
    void renderTabText(RenderTarget&);
    void renderListItemText(RenderTarget&);
    void renderGraph(RenderTarget&);
    void renderEventText(RenderTarget&);
    void initAsset();
    void initEvents();
    void initList();
    
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