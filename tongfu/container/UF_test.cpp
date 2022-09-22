#include "tongfu/container/UF.h"

#include <iostream>

using namespace tongfu;

int main() {
    UF uf(10);

    uf.Union(1, 3);
    uf.Union(3, 5);
    uf.Union(5, 7);
    uf.Union(1, 9);

    uf.Union(0, 2);
    uf.Union(4, 2);
    uf.Union(0, 6);
    uf.Union(6, 8);

    std::cout << "2, 8 should be connected: " << uf.connected(2, 8)
              << std::endl;
    std::cout << "3, 9 should be connected: " << uf.connected(3, 9)
              << std::endl;
    std::cout << "2, 9 shouldn't be connected: " << uf.connected(2, 9)
              << std::endl;
    std::cout << "num of disjoint sets shoud be 2: " << uf.count() << std::endl;
    return 0;
}
