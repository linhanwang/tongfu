#include "tongfu/algorithm/depth_first_search.h"
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

    DepthFirstSearch dfs(g, 0);

    std::cout << "count should be 6: " << dfs.count() << std::endl;

    return 0;
}
