#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

class Graph {
private:
    int vert;
    int sides;
    std::vector<int> side;
    int harevanutyan_m[7][7] = { 0 };  
    int kcutyan_m[22][7] = { 0 };      

public:
    void Dijskrat_alg();
};

#endif
