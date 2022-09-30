#include "tongfu/algorithm/acyclic_sp.h"

#include <fstream>
#include <iostream>

using namespace tongfu;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "./app graph.txt!!!" << std::endl;
    }

    std::ifstream in(argv[1]);
    EdgeWeightedDigraph g = buildEdgeWeightedDigraphFromStdin(in);

    AcyclicSP sp(g, 5);

    for (int t = 0; t < g.V(); ++t) {
        std::cout << 5 << " to " << t << ": " << sp.distTo(t) << "  ";
        if (sp.hasPathTo(t))
            for (DirectedEdge e : sp.pathTo(t)) std::cout << e << "  ";
        std::cout << std::endl;
    }

    return 0;
}
