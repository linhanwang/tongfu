#include "tongfu/container/node_list.h"

#include <iostream>

using namespace tongfu;

template <typename E>
inline void print(const NodeList<E>& l) {
    std::cout << "[";
    for (auto iter = l.begin(); iter != l.end(); ++iter) {
        std::cout << *iter << ",";
    }
    std::cout << "]" << std::endl;
}

int main() {
    NodeList<int> l;
    l.insertFront(1);
    l.insertFront(2);
    l.insertFront(3);

    print(l);

    l.insertBack(4);
    l.insertBack(5);
    l.insertBack(6);

    print(l);

    l.eraseFront();
    l.eraseBack();

    print(l);

    return 0;
}
