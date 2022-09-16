#include "tongfu/container/linked_stack.h"

#include <iostream>
#include <string>

using namespace tongfu;

int main() {
    LinkedStack<std::string> s;
    s.push("linhan");
    s.push("wang");
    s.push("practice");
    s.push("coding");

    std::cout << s << std::endl;

    s.pop();

    std::cout << s << std::endl;
    std::cout << s.top() << std::endl;

    return 0;
}
