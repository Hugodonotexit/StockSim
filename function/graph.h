#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

#define GRAPH_POS_X 400
#define GRAPH_POS_Y 300
#define GRAPH_WIDTH 1400
#define GRAPH_HEIGHT 500

class Graph
{
private:
    std::vector<float> assetPrices = {0,0,0,2,5,6,7,4,3,2,0,0,25,50, 75, 100, 50, 75, 80, 100};
    double maxPriceRange, minPriceRange, priceRange, scale_y;
    int maxRange_x = this->assetPrices.size();
    int minRange_x = 0;
    sf::VertexArray lines;

    void calculatePriceRange();
    
public:
    Graph(float);
    void setmaxRange_x(int);
    int getmaxRange_x();
    void setminRange_x(int);
    int getminRange_x();
    void setminmaxRange_x(int, int);
    void updatGraphPrice(float);
    sf::VertexArray getLines();
    void updateLines();
    ~Graph();
};

#endif