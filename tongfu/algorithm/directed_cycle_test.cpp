#include "tongfu/algorithm/directed_cycle.h"
#include <iostream>
#include "tongfu/algorithm/digraph.h"

using namespace tongfu;

int main() {
    Digraph g = buildDigraphFromStdin();
    DirectedCycle cycle(g);

    std::cout << "hasCycle() : " << cycle.hasCycle() << std::endl;

    for (int v : cycle.cycle()) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
