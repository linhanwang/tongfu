#include "tongfu/container/heap_priority_queue.h"
#include <functional>
#include <iostream>

using namespace tongfu;

int main() {
    HeapPriorityQueue<int, std::less<>> pq;

    pq.insert(3);
    std::cout << "min shoud be 3: " << pq.min() << std::endl;
    std::cout << "size shoud be 1: " << pq.size() << std::endl;

    pq.insert(5);
    std::cout << "min shoud be 3: " << pq.min() << std::endl;

    pq.insert(2);
    std::cout << "min shoud be 2: " << pq.min() << std::endl;

    pq.insert(6);
    pq.insert(7);
    pq.insert(1);
    pq.insert(8);
    std::cout << "min shoud be 1: " << pq.min() << std::endl;

    pq.removeMin();
    std::cout << "min shoud be 2: " << pq.min() << std::endl;

    pq.removeMin();
    std::cout << "min shoud be 3: " << pq.min() << std::endl;
    std::cout << "size shoud be 5: " << pq.size() << std::endl;

    return 0;
}
