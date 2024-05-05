#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

#define GRAPH_POS_X 400
#define GRAPH_POS_Y 300
#define GRAPH_WIDTH 1400
#define GRAPH_HEIGHT 700

class Graph
{
private:
    std::vector<float> assetPrices = {500, 100, 200, 300, 500, 450, 660, 670, 200};
    float maxPriceRange, minPriceRange;
    sf::VertexArray lines;

    void calculatePriceRange();
    void updateLines();
public:
    Graph(float);
    void updatGraphPrice(float);
    sf::VertexArray getLines();
    ~Graph();
};

#endif