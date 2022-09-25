#include "tongfu/algorithm/connected_components.h"
#include <iostream>
#include <vector>

using namespace tongfu;

int main() {
    Graph g(13);

    g.addEdge(0, 5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(6, 7);
    g.addEdge(6, 8);
    g.addEdge(8, 9);
    g.addEdge(10, 11);
    g.addEdge(11, 12);

    CC cc(g);
    int M = cc.count();
    std::vector<std::vector<int>> components(M);
    for (int i = 0; i < g.V(); ++i) {
        components[cc.id(i)].push_back(i);
    }

    for (int i = 0; i < M; ++i) {
        for (int v : components[i]) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
