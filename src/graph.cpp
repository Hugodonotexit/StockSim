#include "../include/graph.h"
void Graph::calculatePriceRange()
{
    if (assetPrices.empty())
    {
        this->maxPriceRange = 0;
        this->minPriceRange = 0;
    } else{
        this->maxPriceRange = *std::max_element(this->assetPrices.begin() + this->minRange_x, this->assetPrices.end() - (this->assetPrices.size() - this->maxRange_x));
        this->minPriceRange = *std::min_element(this->assetPrices.begin() + this->minRange_x, this->assetPrices.end() - (this->assetPrices.size() - this->maxRange_x));
        this->priceRange = this->maxPriceRange - this->minPriceRange;
    }
}

void Graph::updateLines()
{
    this->calculatePriceRange();
    lines.clear();
    scale_y = (GRAPH_HEIGHT - 30 ) / this->priceRange;
    for (int i = this->minRange_x; i < this->maxRange_x; i++)
    {
        float x = (i - minRange_x) * (GRAPH_WIDTH / (maxRange_x - minRange_x));
        float y = GRAPH_HEIGHT - (this->assetPrices[i] - this->minPriceRange) * scale_y - 20;
        lines.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Green));
    }
};

void Graph::updatGraphPrice(float price)
{   
    this->maxRange_x = this->assetPrices.size();
    this->minRange_x = maxRange_x - 365;
    if (this->minRange_x < 0)
    {
        this->minRange_x = 0;
    }
    
    this->assetPrices.push_back(price);
};

void Graph::switchGraph() {

    this->updateLines();
}

void Graph::setminRange_x(int min){
    if (min < 0 || min > this->maxRange_x - 14)
    {
        return;
    }
    this->minRange_x = min;
}

void Graph::setmaxRange_x(int max){
    if (max > (int)this->assetPrices.size() || max < (int)this->minRange_x + 14)
    {
        return;
    }
    this->maxRange_x = max;
}

void Graph::setminmaxRange_x(int min, int max){
    if (min < 0 || min > this->maxRange_x - 14 || max > (int)this->assetPrices.size() || max < (int)this->minRange_x + 14)
    {
        return;
    }
    this->minRange_x = min;
    this->maxRange_x = max;
}

int Graph::getminRange_x() {return this->minRange_x;}
int Graph::getmaxRange_x() {return this->maxRange_x;}

Graph::Graph(float price) : lines(sf::LineStrip, 10)
{
    this->assetPrices.push_back(price);
    this->calculatePriceRange();
}

sf::VertexArray Graph::getLines() {return this->lines;}

Graph::~Graph() {}