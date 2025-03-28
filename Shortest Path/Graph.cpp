#include "Graph.h"
#include <iostream>

void Graph::Dijskrat_alg() {

    std::cout << "Write number of vertices of the graph" << std::endl;

    do {
        std::cin >> vert;
    } while (vert < 1 || vert > 7);

    std::cout << "Write number of sides of the graph" << std::endl;
    do {
        std::cin >> sides;
    } while (sides < 0 || sides > 22);

    side.resize(sides);
    std::cout << "Write vertices of graph in numbers (example 01, 25, ...)" << std::endl;
    for (int i = 0; i < sides; i++) {
        std::cin >> side[i];
    }

    for (int i = 0; i < sides; i++) {
        int a = side[i] / 10;
        int b = side[i] % 10;
        harevanutyan_m[a][b] = 1;
        harevanutyan_m[b][a] = 1;
    }

    int dist[7];
    bool used[7] = { false };
    int pred[7];
    int path[7];
    int start;
    int end;
    int v;
    int l;
    std::cout << "Write start vertex" << std::endl;
    std::cin >> start;
    std::cout << "Write end vertex" << std::endl;
    std::cin >> end;

    for (int i = 0; i < vert; i++) {
        dist[i] = 1000;
        pred[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < vert; ++i) {
        v = -1;
        for (int j = 0; j < vert; ++j) {
            if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }
        if (dist[v] == 1000) break;
        used[v] = true;

        for (int i = 0; i < vert; ++i) {
            if (harevanutyan_m[v][i] && dist[i] > dist[v] + 1) {
                dist[i] = dist[v] + 1;
                pred[i] = v;
            }
        }
    }
    v = end;
    l = 0;
    while (v != -1)
    {
        path[l++] = v;
        v = pred[v];
    }
    if (pred[end] != -1)
    {
        std::cout << "Shortest path from " << start << " to " << end << ": ";
        for (int i = l - 1; i >= 0; i--)
        {
            std::cout << path[i];
            if (i > 0)
                std::cout << "->";
        }
        std::cout << " (" << l - 1 << ")" << std::endl;
    }
    else
        std::cout << "No path from " << start << " to " << end << std::endl;
}
