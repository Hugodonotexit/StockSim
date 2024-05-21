#include "game.h"
Game::Game() {
  this->initWin();
  this->initAsset();
  this->initList();
  this->initEvents();
  this->initBox();
}
Game::~Game() {
  delete this->window;
  delete this->boxInfoContainer;
  delete this->graphContainer;
  delete this->listContainer;
  delete this->sprite;
  delete this->sprite1;
  delete this->sprite2;
  delete this->openedAsset;
  for (int i = 0; i < this->numCryptos; i++) {
    delete cryptos[i];
  }

  for (int i = 0; i < this->numStocks; i++) {
    delete stocks[i];
  }
  for (int i = 0; i < this->numCryptolizedStock; i++)
  {
    delete this->cryptolizedStock[i];
  }
  for (int i = 0; i < TAB_NUM; i++)
  {
    delete this->list[i];
  }
  
  
  for (int i = 0; i < this->numEvents; i++) {
    delete events[i];
  }

  delete[] this->cryptos;
  delete[] this->stocks;
  delete[] this->events;
  delete[] this->cryptolizedStock;
  delete[] this->list;
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
      case Event::MouseButtonPressed:
        /*
        Change time speed with mouse
        Vector2f(35.f, 35.f) sprite offset
        */
        if (Mouse::isButtonPressed(Mouse::Left) &&
            this->boxInfo.getGlobalBounds().contains(this->mousePosView -
                                                     Vector2f(35.f, 35.f))) {
          for (int i = 0; i < TIMECHANGE_MODE; i++) {
            if (this->timeChange[i].getGlobalBounds().contains(
                    this->mousePosView - Vector2f(35.f, 35.f))) {
              this->timeScaleIndex = i;
              this->gametime.setTimeScaleIndex(this->timeScaleIndex);
            }
          }
        }

        if (Mouse::isButtonPressed(Mouse::Left) &&
            this->boxGraph.getGlobalBounds().contains(
                this->mousePosView - Vector2f(GRAPH_POS_X, GRAPH_POS_Y))) {
          this->dragging = true;
          dragOldPostion = mousePosView.x;
        }
        break;
      case Event::MouseButtonReleased:
        if (Mouse::Left) {
          this->dragging = false;
        }
        break;
      case Event::MouseMoved:
        if (this->dragging && this->gametime.getTimeScaleIndex() == 0) {
          int move = (mousePosView.x - dragOldPostion);
          this->openedAsset->setGraph()->setminmaxRange_x(
              (int)(this->openedAsset->setGraph()->getminRange_x() - move),
              (int)(this->openedAsset->setGraph()->getmaxRange_x() - move));
        }
        break;
      case Event::MouseWheelScrolled:
        if (this->boxGraph.getGlobalBounds().contains(
                this->mousePosView - Vector2f(GRAPH_POS_X, GRAPH_POS_Y))) {
                this->openedAsset->setGraph()->setminRange_x((int)(this->openedAsset->setGraph()->getminRange_x() +
                                                  keyEvent.mouseWheelScroll.delta));
        }
        break;
      case Event::KeyPressed:
        switch (keyEvent.key.code) {
          case Keyboard::Escape:
            this->window->close();
            break;
          case Keyboard::Num0:
            this->gametime.setTimeScaleIndex(0);
            break;
          case Keyboard::Num1:
            this->timeScaleIndex = 1;
            this->gametime.setTimeScaleIndex(this->timeScaleIndex);
            break;
          case Keyboard::Num2:
            this->timeScaleIndex = 2;
            this->gametime.setTimeScaleIndex(this->timeScaleIndex);
            break;
          case Keyboard::Num3:
            this->timeScaleIndex = 3;
            this->gametime.setTimeScaleIndex(this->timeScaleIndex);
            break;
          case Keyboard::Num4:
            this->timeScaleIndex = 4;
            this->gametime.setTimeScaleIndex(this->timeScaleIndex);
            break;
          case Keyboard::Space:
          case Keyboard::P:
            if (gametime.getTimeScaleIndex() != 0) {
              this->gametime.setTimeScaleIndex(0);
            } else {
              this->gametime.setTimeScaleIndex(this->timeScaleIndex);
            }
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
  this->updateText();
  this->updateAsset(nullptr);
  this->updateListItemText();
}
void Game::render() {
  // clear flame
  this->boxInfoContainer->clear(Color::Transparent);
  this->graphContainer->clear(Color::Transparent);
  this->listContainer->clear(Color(108, 156, 99));
  this->window->clear(Color(126, 169, 121));  // Main background colour
  // render game objects
  // info
  this->boxInfoContainer->draw(this->boxInfo);
  this->renderInfoText(*this->boxInfoContainer);
  // graph
  this->openedAsset->setGraph()->updateLines();
  this->graphContainer->draw(this->boxGraph);
  this->graphContainer->draw(this->openedAsset->setGraph()->getLines());
  this->renderGraph(*this->graphContainer);

  // list
  for (int i = 0; i < TAB_NUM; i++)
  {
    this->listContainer->draw(this->boxListTab[i]);
  }
    this->renderListItemText(*this->listContainer);
    this->renderTabText(*this->listContainer);

  // sprite
  window->draw(*sprite);
  window->draw(*sprite1);
  window->draw(*sprite2);

  // display flame
  this->boxInfoContainer->display();
  this->graphContainer->display();
  this->listContainer->display();
  this->window->display();
}

// Private Functions

void Game::initWin() {
  this->videoMode.width = 1920;
  this->videoMode.height = 1080;
  this->window = new RenderWindow(this->videoMode, "Stock Sim");
  this->window->setFramerateLimit(60);
  this->window->setPosition(Vector2i(0,0));

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
  // InfoBox
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
    this->timeChange[i].setPosition(
        Vector2f(20.f + 40 * i + 6 * (i - 1) * (i - 1), 145.f));
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

  // Graph
  this->boxGraph.setSize(Vector2f(GRAPH_WIDTH, GRAPH_HEIGHT));
  this->boxGraph.setFillColor(Color(76, 107, 70));
  this->graphContainer = new RenderTexture();
  this->graphContainer->create(GRAPH_WIDTH, GRAPH_HEIGHT);
  this->graphContainer->setSmooth(true);
  this->sprite1 = new Sprite(this->graphContainer->getTexture());
  this->sprite1->setPosition(Vector2f(GRAPH_POS_X, GRAPH_POS_Y));

  //list
    for (int i = 0; i < TAB_NUM; i++)
    {
        this->boxListTab[i].setSize(Vector2f(103,30.f));
        this->boxListTab[i].setPosition(Vector2f(103 * i + 0.5,0));
        this->boxListTab[i].setOutlineThickness(2);
        this->boxListTab[i].setFillColor(Color(76, 107, 70));
        this->boxListTab[i].setOutlineColor(Color(3, 146, 27));
    }
    
    this->listContainer = new RenderTexture();
    this->listContainer->create(310,700);
    this->listContainer->setSmooth(true);

  for (int i = 0; i < TAB_NUM; i++) {
    this->typeTab[i].setFont(this->openSans);
    this->typeTab[i].setFillColor(Color::Black);
    this->typeTab[i].setCharacterSize(16);
    this->typeTab[i].setPosition(Vector2f(103 * i + 5, 5));
    this->typeTab[i].setString(this->list[i]->getName());

  }

  this->sprite2 = new Sprite(this->listContainer->getTexture());
  this->sprite2->setPosition(Vector2f(35.f, 300.f));
  
}

void Game::initList() {
  this->list = new List *[TAB_NUM];
  this->list[0] = new List("Crypto", this->numCryptos, this->cryptos, &this->openSans);
  this->list[1] = new List("Stock", this->numStocks, this->stocks, &this->openSans);
  this->list[2] = new List("Crypto Stock", this->numCryptolizedStock, this->cryptolizedStock, &this->openSans);
}

void Game::updateListItemText() {
  for (int i = 0; i < TAB_NUM; i++)
  {
    this->typeTab[i].setFillColor(Color::Black);
    this->typeTab[this->listIndex].setFillColor(Color::White);
  }

  
  for (int i = 0; i < this->list[this->listIndex]->getIndex(); i++)
  {
    this->list[this->listIndex]->getListItem(i)->updateText();
    this->list[this->listIndex]->getListItem(i)->getText().setPosition(Vector2f(5.f, 16.f * i + 16));
  }
}

void Game::updateAsset(Asset *excludedAsset) {
  if (this->gametime.getDay() != this->oldTime) {
    for (int i = 0; i < this->numStocks; i++) {
      if (excludedAsset != this->stocks[i]) {
        this->stocks[i]->updatePrice();
      }
    }
    for (int i = 0; i < this->numCryptos; i++) {
      if (excludedAsset != this->cryptos[i]) {
        this->cryptos[i]->updatePrice();
      }
    }
    for (int i = 0; i < this->numCryptolizedStock; i++) {
      if (excludedAsset != this->cryptolizedStock[i]) {
        this->cryptolizedStock[i]->updatePrice();
      }
    }
    this->openedAsset->setGraph()->setminmaxRange_x(this->openedAsset->setGraph()->getminRange_x() + 1, this->openedAsset->setGraph()->getmaxRange_x() + 1);
  }
  this->oldTime = this->gametime.getDay();
  std::this_thread::sleep_for(std::chrono::microseconds(10));
}

void Game::updateText() {
  std::stringstream ss;

  ss << "Name: " << player.getName();
  this->infoText[0].setString(ss.str());
  ss.str("");

  ss << "Balance: $" << player.getBalance();
  this->infoText[1].setString(ss.str());
  ss.str("");

  ss << std::setw(2) << std::setfill('0') << gametime.getDay() << "/"
     << std::setw(2) << std::setfill('0') << gametime.getMonth() << "/"
     << std::setw(2) << std::setfill('0') << gametime.getYear();
  this->infoText[2].setString(ss.str());
  ss.str("");

  for (int i = 0; i < TIMECHANGE_MODE; i++) {
    this->timeChange[i].setFillColor(Color::Black);
    this->timeChange[gametime.getTimeScaleIndex()].setFillColor(Color::White);
  }
};
void Game::renderInfoText(RenderTarget &target) {
  for (int i = 0; i < INFOTEXT_LINE; i++) {
    target.draw(this->infoText[i]);
  }

  for (int i = 0; i < TIMECHANGE_MODE; i++) {
    target.draw(this->timeChange[i]);
  }
}

void Game::renderTabText(RenderTarget &target) {
  for (int i = 0; i < TAB_NUM; i++)
  {
    target.draw(this->typeTab[i]);
  }
}

void Game::renderListItemText(RenderTarget &target) {
  for (int i = 0; i < this->list[this->listIndex]->getIndex(); i++) {
    target.draw(this->list[this->listIndex]->getListItem(i)->getText());
  }
}

void Game::renderGraph(RenderTarget &target) {
  target.draw(this->openedAsset->setGraph()->getLines());
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
    getline(iss, sector, ',');
    getline(iss, name, ',');
    getline(iss, ticker, ',');
    iss >> price;  
    iss.ignore();  
    iss >> circulatingShares;

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

    getline(iss, name, ',');
    getline(iss, ticker, ',');
    iss >> price;  
    iss.ignore();  
    iss >> circulatingAmount;
    cryptos[i] = new Crypto(name, ticker, price, circulatingAmount);
  }

  //cryptolizedStock
  srand(rand());
  this->numCryptolizedStock = (rand() % 10 + 2);

  this->cryptolizedStock = new Asset *[this->numCryptolizedStock];

  for (int i = 0; i < this->numCryptolizedStock; i++)
  {
    this->cryptolizedStock[i] = new CryptolizedStock(static_cast<Stock*>(stocks[rand() % this->numStocks]));
  }

  this->openedAsset = cryptos[0];
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
