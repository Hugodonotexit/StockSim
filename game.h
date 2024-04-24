//Game front end
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>

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


    //Objects
    

    //Functions
    void initVar();
    void initWin();

public:
    Game();
    ~Game();

    //Functions
    const bool getWinIsOpen();
    void randUpdate();
    void mousePosUpdate();
    void eventUpdate(); //check keys input
    void update();
    void render();
};


#endif