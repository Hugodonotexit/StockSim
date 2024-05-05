#include "graph.h"

void Graph::calculatePriceRange()
{
    if (assetPrices.empty())
    {
        this->maxPriceRange = 0;
        this->minPriceRange = 0;
    } else{
        this->maxPriceRange = *std::max_element(this->assetPrices.begin(), this->assetPrices.end());
        this->minPriceRange = *std::min_element(this->assetPrices.begin(), this->assetPrices.end());
    }
}

void Graph::updateLines()
{
    lines.clear();
    if (assetPrices.size() < 2) {return;}
    float scale_y = this->graphHeight / (this->maxPriceRange - this->minPriceRange);
    for (size_t i = 0; i < this->assetPrices.size(); i++)
    {
        float x = i * (this->graphWidth / (this->assetPrices.size() - 1));
        float y = graphHeight - (this->assetPrices[i] - this->minPriceRange) * scale_y;
        lines.append(sf::Vertex(sf::Vector2f(x, y), sf::Color::Green));
    }
};

void Graph::updatGraphPrice(float price)
{
    this->assetPrices.push_back(price);
    this->calculatePriceRange();
    this->updateLines();
};

Graph::Graph(float price) : lines(sf::LineStrip, 10)
{
    this->assetPrices.push_back(price);
    this->calculatePriceRange();
}

sf::VertexArray Graph::getLines() {return this->lines;}

Graph::~Graph() {}