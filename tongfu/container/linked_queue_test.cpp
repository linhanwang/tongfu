#include "tongfu/container/linked_queue.h"
#include <iostream>

using namespace tongfu;

int main() {
    LinkedQueue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    std::cout << "After enqueue 1,2,3: " << q << std::endl;

    std::cout << "front(): " << q.front() << std::endl;
    q.dequeue();

    std::cout << "front(): " << q.front() << std::endl;
    q.dequeue();

    std::cout << "front(): " << q.front() << std::endl;
    q.dequeue();

    return 0;
}
