#include <iostream>
#include "game.h"

using namespace sf;

int main() {
  // Init Game front end
  Game stockSim;

  // Game loop
  while (stockSim.getWinIsOpen()) {
    Event event;
    stockSim.update();
    stockSim.render();
  }
  return 0;
}