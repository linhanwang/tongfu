#include "tongfu/algorithm/kosaraju_scc.h"
#include <iostream>
#include <vector>
#include "tongfu/algorithm/digraph.h"
using namespace tongfu;
int main() {
    Digraph g = buildDigraphFromStdin();
    KosarajuSCC scc(g);
    int m = scc.count();
    std::cout << m << " strong components" << std::endl;

    std::vector<std::vector<int>> components(m);
    for (int v = 0; v < g.V(); ++v) {
        components[scc.id(v)].push_back(v);
    }

    for (int i = 0; i < m; ++i) {
        for (int v : components[i])
            std::cout << v << " ";
        std::cout << std::endl;
    }

    return 0;
}
