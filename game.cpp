#include "game.h"

Game::Game() {
  this->initVar();
  this->initWin();
}
Game::~Game() { delete this->window; }

// Public Functions
const bool Game::getWinIsOpen() { return this->window->isOpen(); }
void Game::eventUpdate() {
  // check keys input
  while (this->window->pollEvent(this->keyEvent)) {
    this->randSeed += (this->keyEvent.mouseMove.x *
                       this->keyEvent.mouseMove.y);  // set randSeed
    srand(this->randSeed);
    switch (keyEvent.type) {
      case Event::Closed:
        window->close();
        break;

      case Event::KeyPressed:
        switch (keyEvent.key.code) {
          case Keyboard::Escape:
            window->close();
            break;
          default:
            this->randSeed /= (this->keyEvent.mouseMove.x * (1000 + rand()) +
                               this->keyEvent.mouseMove.y /
                                   abs((1 - rand())));  // set randSeed
            break;
        }
        break;
    }
  }
}
void Game::update() { this->eventUpdate(); }
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
  this->window =
      new RenderWindow(this->videoMode.getDesktopMode(), "Stock Sim", Style::Fullscreen);
  this->window->setVerticalSyncEnabled(true);
}