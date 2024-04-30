#include <iostream>
#include "game.h"

int main() {
  // Init Game engine
  Game stockSim;

  // Game loop
  while (stockSim.getWinIsOpen()) {
    stockSim.update();
    stockSim.render();
  }
  return 0;
}