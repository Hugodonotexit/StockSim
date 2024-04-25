#include "game.h"

Game::Game() {
  this->initWin();
  this->initAsset();
}
Game::~Game() { 
  delete this->window; 
  for (int i = 0; i < this->numCryptos; i++)
  {
    delete cryptos[i];
  }
  /*
  for (int i = 0; i < this->numForexs; i++)
  {
    delete forexs[i];
  }
  */
  for (int i = 0; i < this->numStocks; i++)
  {
    delete stocks[i];
  }
  
  delete[] this->cryptos;
  //delete[] this->forexs;
  delete[] this->stocks;
  }

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
        this->window->close();
        break;
      default:
        /*keep emptry*/
        break;

      case Event::KeyPressed:
        switch (keyEvent.key.code) {
          case Keyboard::Escape:
            this->window->close();
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
  this->numStocks = 0;

  if (!stock_file) {
    std::cerr << "Failed to open stocks file." << std::endl;
    this->window->close();
    return;
  }

  while (getline(stock_file, stock_line)) {
    this->numStocks++;
  }

  stocks = new Asset*[this->numStocks];

  stock_file.clear();
  stock_file.seekg(0, std::ios::beg);
  
  for (int i = 0; i < this->numStocks; i++)
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
  this->numCryptos = 0;

  if (!crypto_file) {
    std::cerr << "Failed to open cryptos file." << std::endl;
    this->window->close();
    return;
  }
  
  while (getline(crypto_file, crypto_line)) {
    this->numCryptos++;
  }

  cryptos = new Asset*[this->numCryptos];
  crypto_file.clear();
  crypto_file.seekg(0, std::ios::beg);
  
  for (int i = 0; i < this->numCryptos; i++)
  {
    getline(crypto_file, crypto_line);
    std::istringstream iss(crypto_line);
    std::string name, ticker;
    float price;
    iss >> name >> ticker >> price >> circulatingAmount;
    cryptos[i] = new Crypto(name, ticker, price, circulatingAmount);
  }

  /*
  //forex
  std::ifstream forex_file("db/forexs.txt");
  std::string forex_line;
  this->numForexs = 0;

  if (!forex_file) {
    std::cerr << "Failed to open forexs file." << std::endl;
    this->window->close();
    return;
  }

  while (getline(forex_file, forex_line)) {
    this->numForexs++;
  }

  forexs = new Asset*[this->numForexs];

  forex_file.clear();
  forex_file.seekg(0, std::ios::beg);
  
  for (int i = 0; i < this->numForexs; i++)
  {
    getline(forex_file, forex_line);
    std::istringstream iss(forex_line);
    std::string name, ticker;
    float price;
    iss >> name >> ticker >> price;
    forexs[i] = new Forex(name, ticker, price);
  }
  */
};
