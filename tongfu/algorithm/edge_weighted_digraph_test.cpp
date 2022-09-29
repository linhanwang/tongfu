#include "tongfu/algorithm/edge_weighted_digraph.h"
#include <fstream>
#include <iostream>

using namespace tongfu;

int main(int argc, char** argv) {
    std::ifstream in(argv[1]);
    EdgeWeightedDigraph g = buildEdgeWeightedDigraphFromStdin(in);

    for (DirectedEdge e : g.edges()) {
        std::cout << e << std::endl;
    }

    return 0;
}
