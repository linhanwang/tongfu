#include "tongfu/algorithm/lazy_prime_mst.h"
#include <fstream>
#include <iostream>

using namespace tongfu;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "./app graph.txt!!!" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    EdgeWeightedGraph g = buildEdgeWeightedGraphFromStdin(in);

    LazyPrimeMST mst(g);
    for (Edge e : mst.edges())
        std::cout << e << std::endl;
    std::cout << mst.weight() << std::endl;
    return 0;
}
