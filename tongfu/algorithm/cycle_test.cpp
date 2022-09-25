#include "tongfu/algorithm/cycle.h"
#include <iostream>

using namespace tongfu;
int main() {
    {
        Graph g(6);
        g.addEdge(0, 1);
        g.addEdge(0, 3);
        g.addEdge(2, 4);
        g.addEdge(4, 5);
        
        Cycle cycle(g);
        std::cout << "g hasn't cylce: " << cycle.hasCycle() << std::endl;
    }
    
    {
        Graph g(6);
        g.addEdge(0, 1);
        g.addEdge(0, 3);
        g.addEdge(2, 4);
        g.addEdge(4, 5);
        g.addEdge(1, 3);
        
        Cycle cycle(g);
        std::cout << "g has cylce: " << cycle.hasCycle() << std::endl;
    }

    return 0;
}
