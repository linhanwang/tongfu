#include "tongfu/container/circularly_linked_list.h"

#include <iostream>
#include <string>

using namespace tongfu;

int main() {
    CircleList<std::string> l;
    l.addFront("Stayin Alive");
    l.addFront("Le Freak");
    l.addFront("Jive Talkin");

    std::cout << l << std::endl;

    l.advance();
    l.advance();

    std::cout << l << std::endl;

    l.removeFront();
    l.addFront("Disco Inferno");

    std::cout << l << std::endl;

    return 0;
}
