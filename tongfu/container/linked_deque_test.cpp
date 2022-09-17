#include "tongfu/container/linked_deque.h"
#include <iostream>

using namespace tongfu;

int main() {
    LinkedDeque<int> q;

    q.insertFront(1);
    q.insertFront(2);
    q.insertFront(3);
    q.insertBack(4);
    q.insertBack(5);
    q.insertBack(6);

    std::cout << q << std::endl;

    q.removeFront();

    std::cout << q << std::endl;
    
    q.removeBack();

    std::cout << q << std::endl;
    
    std::cout << "front: " << q.front() << " back: " << q.back() << std::endl;

    return 0;
}
