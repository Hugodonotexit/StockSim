#include "game.h"

Game::Game() {
  this->initWin();
  this->initAsset();
  this->initEvents();
  this->initBox();
}
Game::~Game() {
  delete this->window;
  delete this->boxInfoContainer;
  delete this->sprite;
  for (int i = 0; i < this->numCryptos; i++) {
    delete cryptos[i];
  }
  /*
  for (int i = 0; i < this->numForexs; i++)
  {
    delete forexs[i];
  }
  */
  for (int i = 0; i < this->numStocks; i++) {
    delete stocks[i];
  }
  for (int i = 0; i < this->numEvents; i++) {
    delete events[i];
  }

  delete[] this->cryptos;
  // delete[] this->forexs;
  delete[] this->stocks;
  delete[] this->events;
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

      case Event::KeyPressed:
        switch (keyEvent.key.code) {
          case Keyboard::Escape:
            this->window->close();
            break;
          case Keyboard::Num0:
          case Keyboard::P:
            this->gametime.setTimeScale(0);
            break;
          case Keyboard::Num1:
            this->gametime.setTimeScale(4);
            break;
          case Keyboard::Num2:
            this->gametime.setTimeScale(8);
            break;
          case Keyboard::Num3:
            this->gametime.setTimeScale(16);
            break;
          case Keyboard::Num4:
            this->gametime.setTimeScale(32);
            break;
          default:
            /*keep emptry*/
            break;
        }
        break;
      default:
        /*keep emptry*/
        break;
    }
  }
}
void Game::update() {
  this->eventUpdate();
  this->mousePosUpdate();
  this->gametime.updateTime();
  this->player.updateMargin();
  this->updateText();
}
void Game::render() {
  // clear flame
  this->boxInfoContainer->clear(Color::Transparent);
  this->window->clear(Color(121, 164, 113));  // Main background colour
  // render game objects
  this->boxInfoContainer->draw(this->boxInfo);
  this->renderText(*this->boxInfoContainer);
  window->draw(*sprite);

  // display flame
  this->window->display();
  this->boxInfoContainer->display();
}

// Private Functions

void Game::initWin() {
  this->window = new RenderWindow(this->videoMode.getDesktopMode(), "Stock Sim",
                                  Style::Fullscreen);
  this->window->setFramerateLimit(60);

  if (!this->openSans.loadFromFile("font/Opensans/OpenSans-Regular.ttf"))
  {
    std::cerr << "Failed to open OpenSans-Regular.ttf file." << std::endl;
    this->window->close();
  }

  if (!this->pixeBoy.loadFromFile("font/Pixeboy/Pixeboy-z8XGD.ttf")) {
    std::cerr << "Failed to open Pixeboy-z8XGD.ttf file." << std::endl;
    this->window->close();
  }
}

void Game::initBox() {
  // Text & font
  this->boxInfoContainer = new RenderTexture();
  this->boxInfoContainer->create(310,190);
  for (int i = 0; i < INFOTEXT_LINE; i++) {
    this->infoText[i].setFont(this->pixeBoy);
    this->infoText[i].setFillColor(Color::Black);
    this->infoText[i].setCharacterSize(32);
    this->infoText[i].setString("NULL");
    this->infoText[i].setPosition(Vector2f(20.f, 10.f + 32 * i));
  }
  this->sprite = new Sprite(this->boxInfoContainer->getTexture());
  this->sprite->setPosition(Vector2f(35.f,35.f));

  this->boxInfo.setSize(Vector2f(300.f, 180.f));
  this->boxInfo.setOutlineThickness(6);
  this->boxInfo.setFillColor(Color(108, 156, 99));
  this->boxInfo.setOutlineColor(Color(76, 107, 70));
  this->boxInfo.setPosition(Vector2f(10.f, 10.f));
}

void Game::updateText(){
  std::stringstream ss;

  ss << "Name: " << player.getName();
  this->infoText[0].setString(ss.str());
  ss.str("");

  ss << "Balance: $" << player.getBalance();
  this->infoText[1].setString(ss.str());
  ss.str("");

  ss << "Margin: $" << player.getMargin();
  this->infoText[2].setString(ss.str());
  ss.str("");
  
  ss << std::setw(2) << std::setfill('0') << gametime.getDay() << "/" << std::setw(2) << std::setfill('0') << gametime.getMonth() << "/" << std::setw(2) << std::setfill('0') << gametime.getYear() /*<< "  " << std::setw(2) << std::setfill('0') << gametime.getHour() << ":" << std::setw(2) << std::setfill('0') << gametime.getMinute()*/ ;
  this->infoText[3].setString(ss.str());
  ss.str("");

  this->infoText[4].setString("||   >   >>   >>>   >>>>");
};
void Game::renderText(RenderTarget &target) { 
  for (int i = 0; i < INFOTEXT_LINE; i++)
  {
    target.draw(this->infoText[i]); 
  }
  }

void Game::initAsset() {
  // stocks
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

  stocks = new Asset *[this->numStocks];

  stock_file.clear();
  stock_file.seekg(0, std::ios::beg);

  for (int i = 0; i < this->numStocks; i++) {
    getline(stock_file, stock_line);
    std::istringstream iss(stock_line);
    std::string name, ticker;
    float price;
    iss >> sector >> name >> ticker >> price >> circulatingShares;
    stocks[i] = new Stock(sector, name, ticker, price, circulatingShares);
  }

  // crypto
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

  cryptos = new Asset *[this->numCryptos];
  crypto_file.clear();
  crypto_file.seekg(0, std::ios::beg);

  for (int i = 0; i < this->numCryptos; i++) {
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

void Game::initEvents() {
  std::ifstream event_file("db/events.txt");
  std::string nameID, discerption;
  float eventImpactMean, eventImpactStdDev;
  std::string event_line;
  this->numEvents = 0;

  if (!event_file) {
    std::cerr << "Failed to open events file." << std::endl;
    this->window->close();
    return;
  }

  while (getline(event_file, event_line)) {
    this->numEvents++;
  }

  events = new Events *[this->numEvents];

  event_file.clear();
  event_file.seekg(0, std::ios::beg);

  for (int i = 0; i < this->numEvents; i++) {
    getline(event_file, event_line);
    std::istringstream iss(event_line);
    std::string name, ticker;
    iss >> nameID >> discerption >> eventImpactMean >> eventImpactStdDev;
    events[i] =
        new Events(nameID, discerption, eventImpactMean, eventImpactStdDev);
  }
};
