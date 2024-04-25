#include "game.h"

Game::Game() {
  this->initVar();
  this->initWin();
  this->initAsset();
}
Game::~Game() { delete this->window; }

// Public Functions
const bool Game::getWinIsOpen() { return this->window->isOpen(); }

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
      default:
        /*keep emptry*/
        break;

      case Event::KeyPressed:
        switch (keyEvent.key.code) {
          case Keyboard::Escape:
            window->close();
            break;
          default:
            /*keep emptry*/
            break;
        }
        break;
    }
  }
}
void Game::update() {
  this->eventUpdate();
  this->mousePosUpdate();
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
  this->cryptos = nullptr;
  this->forexs = nullptr;
  this->stocks = nullptr;
}
void Game::initWin() {
  this->window = new RenderWindow(this->videoMode.getDesktopMode(), "Stock Sim",
                                  Style::Fullscreen);
  this->window->setFramerateLimit(60);
}
void Game::initAsset() {
  //stocks
  std::ifstream stock_file("db/stocks.txt");
  std::string sector;
  std::string stock_line;
  unsigned long long circulatingShares;
  int numStocks = 0;
  while (getline(stock_file, stock_line)) {
    numStocks++;
  }

  stocks = new Asset*[numStocks];

  stock_file.clear();
  stock_file.seekg(0, std::ios::beg);
  
  for (int i = 0; i < numStocks; i++)
  {
    getline(stock_file, stock_line);
    std::istringstream iss(stock_line);
    std::string name, ticker;
    float price;
    iss >> sector >> name >> ticker >> price >> circulatingShares;
    stocks[i] = new Stock(sector, name, ticker, price, circulatingShares);
  }

  //crypto
  std::ifstream crypto_file("db/cryptos.txt");
  std::string crypto_line;
  unsigned long long circulatingAmount;
  int numCryptos = 0;
  
  while (getline(crypto_file, crypto_line)) {
    numCryptos++;
  }

  cryptos = new Asset*[numCryptos];
  crypto_file.clear();
  crypto_file.seekg(0, std::ios::beg);
  
  for (int i = 0; i < numStocks; i++)
  {
    getline(crypto_file, crypto_line);
    std::istringstream iss(crypto_line);
    std::string name, ticker;
    float price;
    iss >> name >> ticker >> price >> circulatingAmount;
    cryptos[i] = new Crypto(name, ticker, price, circulatingAmount);
  }

  //forex
  std::ifstream forex_file("db/forexs.txt");
  std::string forex_line;
  int numforexs = 0;
  while (getline(forex_file, forex_line)) {
    numforexs++;
  }

  forexs = new Asset*[numforexs];

  forex_file.clear();
  forex_file.seekg(0, std::ios::beg);
  
  for (int i = 0; i < numStocks; i++)
  {
    getline(forex_file, forex_line);
    std::istringstream iss(forex_line);
    std::string name, ticker;
    float price;
    iss >> name >> ticker >> price;
    forexs[i] = new Forex(name, ticker, price);
  }

  
};