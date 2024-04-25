#include "game.h"

Game::Game() {
  this->initVar();
  this->initWin();
}
Game::~Game() { delete this->window; }

// Public Functions
const bool Game::getWinIsOpen() { return this->window->isOpen(); }

void Game::randUpdate() {
  // set randSeed base on mouse position
  if (rand() % 2 == 0) {
    this->randSeed +=
        (this->mousePosWin.x *
         this->mousePosWin.y);  
  } else {
    this->randSeed *=
        (this->mousePosWin.x /
         this->mousePosWin.y); 
  }

  // reset randSeed base on time
  if (sizeof(this->randSeed) >= (sizeof(double) * 0.95)) {
    this->randSeed = time(nullptr);  
  }
  srand(this->randSeed);
}

void Game::mousePosUpdate() {
  this->mousePosWin.x = Mouse::getPosition(*this->window).x;
  this->mousePosWin.y = Mouse::getPosition(*this->window).y;
}

void Game::eventUpdate() {
  // check keys input
  while (this->window->pollEvent(this->keyEvent)) {
    switch (keyEvent.type) {
      case Event::Closed:
        window->close();
        break;

      case Event::KeyPressed:
        switch (keyEvent.key.code) {
          case Keyboard::Escape:
            window->close();
            break;
        }
        break;
    }
  }
}
void Game::update() {
  this->eventUpdate();
  this->mousePosUpdate();
  this->randUpdate();
}
void Game::render() {
  // clear flame
  // render game objects
  // display flame
  this->window->clear(Color(121, 164, 113, 200));  // Main background colour

  this->window->display();
}

// Private Functions
void Game::initVar() {
  this->window = nullptr;
  this->randSeed = time(nullptr);
}
void Game::initWin() {
  this->window = new RenderWindow(this->videoMode.getDesktopMode(),
                                  "Stock Sim", Style::Fullscreen);
  this->window->setFramerateLimit(60);
}