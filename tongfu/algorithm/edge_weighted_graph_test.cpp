#include "tongfu/algorithm/edge_weighted_graph.h"
#include <fstream>
#include <iostream>

using namespace tongfu;

int main(int argc, char** argv) {
    std::ifstream in(argv[1]);
    EdgeWeightedGraph g = buildEdgeWeightedGraphFromStdin(in);

    for (Edge e : g.edges()) {
        std::cout << e << std::endl;
    }

    return 0;
}
