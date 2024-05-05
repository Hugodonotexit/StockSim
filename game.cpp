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
  delete this->graphContainer;
  delete this->sprite;
  delete this->sprite1;
  for (int i = 0; i < this->numCryptos; i++) {
    delete cryptos[i];
  }

  for (int i = 0; i < this->numStocks; i++) {
    delete stocks[i];
  }
  for (int i = 0; i < this->numEvents; i++) {
    delete events[i];
  }

  delete[] this->cryptos;
  delete[] this->stocks;
  delete[] this->events;
}

// Public Functions
const bool Game::getWinIsOpen() { return this->window->isOpen(); }

void Game::mousePosUpdate() {
  this->mousePosWin = Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWin);
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
            this->gametime.setTimeScaleIndex(0);
            break;
          case Keyboard::Num1:
            this->gametime.setTimeScaleIndex(1);
            break;
          case Keyboard::Num2:
            this->gametime.setTimeScaleIndex(2);
            break;
          case Keyboard::Num3:
            this->gametime.setTimeScaleIndex(3);
            break;
          case Keyboard::Num4:
            this->gametime.setTimeScaleIndex(4);
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
  /*
  Change time speed with mouse
  Vector2f(35.f, 35.f) sprite offset
  */
  if (Mouse::isButtonPressed(Mouse::Left)) {
    for (int i = 0; i < TIMECHANGE_MODE; i++) {
      if (this->timeChange[i].getGlobalBounds().contains(this->mousePosView - Vector2f(35.f, 35.f))) {
        this->gametime.setTimeScaleIndex(i);
      }
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
  this->graphContainer->clear(Color(76, 107, 70));
  this->window->clear(Color(126, 169, 121));  // Main background colour
  // render game objects
  this->boxInfoContainer->draw(this->boxInfo);
  this->renderText(*this->boxInfoContainer);
  this->graphContainer->draw(cryptos[0]->getLines());
  this->renderGraph(*this->graphContainer);
  window->draw(*sprite);
  window->draw(*sprite1);

  // display flame
  this->boxInfoContainer->display();
  this->graphContainer->display();
  this->window->display();

}

// Private Functions

void Game::initWin() {
  this->window = new RenderWindow(this->videoMode.getDesktopMode(), "Stock Sim",
                                  Style::Fullscreen);
  this->window->setFramerateLimit(60);

  if (!this->openSans.loadFromFile("font/Opensans/OpenSans-Regular.ttf")) {
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
  this->boxInfoContainer->create(310, 190);
  this->boxInfoContainer->setSmooth(true);
  for (int i = 0; i < INFOTEXT_LINE; i++) {
    this->infoText[i].setFont(this->pixeBoy);
    this->infoText[i].setFillColor(Color::Black);
    this->infoText[i].setCharacterSize(32);
    this->infoText[i].setString("NULL");
    this->infoText[i].setPosition(Vector2f(20.f, 10.f + 32 * i));
  }

  for (int i = 0; i < TIMECHANGE_MODE; i++) {
    this->timeChange[i].setFont(this->pixeBoy);
    this->timeChange[i].setFillColor(Color::Black);
    this->timeChange[i].setCharacterSize(32);
    this->timeChange[i].setString("NULL");
    this->timeChange[i].setPosition(Vector2f(20.f + 40 * i + 6 * (i - 1) * (i - 1), 145.f));
  }

  this->timeChange[0].setString("||");
  this->timeChange[1].setString(">");
  this->timeChange[2].setString(">>");
  this->timeChange[3].setString(">>>");
  this->timeChange[4].setString(">>>>");

  this->sprite = new Sprite(this->boxInfoContainer->getTexture());
  this->sprite->setPosition(Vector2f(35.f, 35.f));

  this->boxInfo.setSize(Vector2f(300.f, 180.f));
  this->boxInfo.setOutlineThickness(6);
  this->boxInfo.setFillColor(Color(108, 156, 99));
  this->boxInfo.setOutlineColor(Color(76, 107, 70));
  this->boxInfo.setPosition(Vector2f(10.f, 10.f));

  //Graph
  this->cryptos[0]->setPrice(100);
  this->graphContainer = new RenderTexture();
  this->graphContainer->create(GRAPH_WIDTH, GRAPH_HEIGHT);
  this->sprite1 = new Sprite(this->graphContainer->getTexture());
  this->sprite1->setPosition(Vector2f(GRAPH_POS_X , GRAPH_POS_Y));
}

void Game::updateText() {
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

  ss << std::setw(2) << std::setfill('0') << gametime.getDay() << "/"
     << std::setw(2) << std::setfill('0') << gametime.getMonth() << "/"
     << std::setw(2) << std::setfill('0')
     << gametime.getYear() /*<< "  " << std::setw(2) << std::setfill('0') <<
                              gametime.getHour() << ":" << std::setw(2) <<
                              std::setfill('0') << gametime.getMinute()*/
      ;
  this->infoText[3].setString(ss.str());
  ss.str("");
};
void Game::renderText(RenderTarget &target) {
  for (int i = 0; i < INFOTEXT_LINE; i++) {
    target.draw(this->infoText[i]);
  }

  for (int i = 0; i < TIMECHANGE_MODE; i++) {
    target.draw(this->timeChange[i]);
  }
}

void Game::renderGraph(RenderTarget &target) {
  target.draw(cryptos[0]->getLines());
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
