#include "tongfu/algorithm/depth_first_paths.h"
#include <iostream>

using namespace tongfu;

int main() {
    Graph g(6);

    g.addEdge(0, 5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);

    g.addEdge(1, 2);
    
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    
    g.addEdge(3, 4);
    g.addEdge(3, 5);

    DepthFirstPaths search(g, 0);
    for (int v = 0; v < g.V(); ++v) {
        std::cout << 0 << " to " << v << ": ";
        for (int x : search.pathTo(v)) {
            if (x == 0) std::cout << x;
            else std::cout << "-" << x;
        }
        std::cout << std::endl;
    }
    return 0;
}
