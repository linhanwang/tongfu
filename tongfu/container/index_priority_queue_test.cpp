#include "tongfu/container/index_priority_queue.h"

#include <iostream>

using namespace tongfu;

int main() {
    IndexPQ<double> pq(6);

    pq.insert(0, 5.0);
    pq.insert(3, 2.0);
    pq.insert(1, 4.0);
    pq.insert(2, 3.0);
    pq.insert(4, 1.0);
    pq.insert(5, 0.0);

    std::cout << "pq contains 3: " << pq.contains(3) << std::endl;

    pq.changeKey(3, 6.0);

    std::cout << "topIndex: " << pq.topIndex() << " topKey: " << pq.topKey()
              << std::endl;
    pq.pop();

    std::cout << "topIndex: " << pq.topIndex() << " topKey: " << pq.topKey()
              << std::endl;
    pq.pop();

    std::cout << "topIndex: " << pq.topIndex() << " topKey: " << pq.topKey()
              << std::endl;
    pq.pop();

    std::cout << "topIndex: " << pq.topIndex() << " topKey: " << pq.topKey()
              << std::endl;
    pq.pop();

    std::cout << "topIndex: " << pq.topIndex() << " topKey: " << pq.topKey()
              << std::endl;
    pq.pop();

    std::cout << "topIndex: " << pq.topIndex() << " topKey: " << pq.topKey()
              << std::endl;
    pq.pop();

    return 0;
}
