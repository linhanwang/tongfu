#include "tongfu/algorithm/directed_dfs.h"

#include <iostream>

#include "tongfu/algorithm/digraph.h"

using namespace tongfu;
int main() {
    Digraph g = buildDigraphFromStdin();

    DirectedDfs dfs(g, 0);

    std::cout << "count should be 6: " << dfs.count() << std::endl;

    DirectedDfs dfs2(g, 6);

    std::cout << "count should be 12: " << dfs2.count() << std::endl;

    return 0;
}
