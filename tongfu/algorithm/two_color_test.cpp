#include "tongfu/algorithm/two_color.h"

#include <iostream>

#include "tongfu/algorithm/graph.h"

using namespace tongfu;

int main() {
    {
        Graph g(6);

        g.addEdge(0, 5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);

        g.addEdge(1, 2);

        g.addEdge(2, 3);
        g.addEdge(2, 4);

        g.addEdge(3, 4);
        g.addEdge(3, 5);

        TwoColor twoColor(g);

        std::cout << "graph is not bipartite: " << twoColor.isBipartite()
                  << std::endl;
    }

    {
        Graph g(13);

        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 5);
        g.addEdge(0, 6);

        g.addEdge(1, 3);

        g.addEdge(3, 5);

        g.addEdge(4, 5);
        g.addEdge(4, 6);

        g.addEdge(7, 6);
        g.addEdge(7, 8);

        g.addEdge(10, 8);

        g.addEdge(9, 10);
        g.addEdge(9, 11);
        g.addEdge(10, 12);

        g.addEdge(11, 12);

        TwoColor twoColor(g);

        std::cout << "graph is bipartite: " << twoColor.isBipartite()
                  << std::endl;
    }
    return 0;
}
