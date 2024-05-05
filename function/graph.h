#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>


class Graph
{
private:
    const int graphWidth = 1400;
    const int graphHeight = 700;

    std::vector<float> assetPrices = {100,200,300,400,05,900,70,800,89,710,90,80,70,60,50,44,13,52,11,11,11,11,11,11,11,11,50,1800,1500,1500};
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