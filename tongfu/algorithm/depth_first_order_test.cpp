#include "tongfu/algorithm/depth_first_order.h"

#include <iostream>
#include <vector>

#include "tongfu/algorithm/digraph.h"

using namespace tongfu;

inline void printVec(const std::vector<int>& vec) {
    for (int v : vec) std::cout << v << " ";
    std::cout << std::endl;
}

int main() {
    Digraph g = buildDigraphFromStdin();

    DepthFirstOrder order(g);

    std::cout << "pre: ";
    printVec(order.pre());

    std::cout << "post: ";
    printVec(order.post());

    std::cout << "reversePost: ";
    printVec(order.reversePost());
    return 0;
}
