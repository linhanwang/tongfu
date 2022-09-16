#include "tongfu/container/doubly_linked_list.h"

#include <iostream>
#include <string>

using namespace tongfu;

int main() {
    {
        DLinkedList<int> l;

        l.addFront(1);

        std::cout << "front() shoud be 1: " << l.front() << std::endl;

        l.addFront(2);
        l.addFront(3);

        std::cout << "After addFront 1,2,3: " << l << std::endl;

        l.addBack(4);
        l.addBack(5);
        l.addBack(6);
        std::cout << "After addBack 4,5,6: " << l << std::endl;

        std::cout << "back() should be 6: " << l.back() << std::endl;

        l.removeBack();
        l.removeBack();
        std::cout << "After removeBack() twice: " << l << std::endl;

        l.removeFront();
        l.removeFront();
        std::cout << "After removeFront() twice: " << l << std::endl;
    }

    {
        DLinkedList<std::string> l;

        l.addFront("1");

        std::cout << "front() shoud be 1: " << l.front() << std::endl;

        l.addFront("2");
        l.addFront("3");

        std::cout << "After addFront 1,2,3: " << l << std::endl;

        l.addBack("4");
        l.addBack("5");
        l.addBack("6");
        std::cout << "After addBack 4,5,6: " << l << std::endl;

        std::cout << "back() should be 6: " << l.back() << std::endl;

        l.removeBack();
        l.removeBack();
        std::cout << "After removeBack() twice: " << l << std::endl;

        l.removeFront();
        l.removeFront();
        std::cout << "After removeFront() twice: " << l << std::endl;
    }

    
    return 0;
}
