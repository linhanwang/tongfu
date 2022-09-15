#include "tongfu/containers/singly_linked_list.h"

#include <iostream>
#include <string>

using namespace tongfu::containers;

int main() {
    SLinkedList<int> l;
    l.addFront(1);
    l.addFront(2);
    l.addFront(3);
    l.addFront(4);

    std::cout << "After addFront 1,2,3,4: " << l << std::endl;

    l.removeFront();
    l.removeFront();

    std::cout << "After removeFront twice: " << l << std::endl;
    std::cout << "front is: " << l.front() << std::endl;
    
    SLinkedList<std::string> l2;
    l2.addFront("1");
    l2.addFront("2");
    l2.addFront("3");
    l2.addFront("4");

    std::cout << "After addFront 1,2,3,4: " << l2 << std::endl;

    l2.removeFront();
    l2.removeFront();

    std::cout << "After removeFront twice: " << l2 << std::endl;
    std::cout << "front is: " << l2.front() << std::endl;
    return 0;
}
