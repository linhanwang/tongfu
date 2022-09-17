#include "tongfu/container/linked_binary_tree.h"
#include <iostream>

using namespace tongfu;

template<typename E>
void printBT(const typename LinkedBinaryTree<E>::PositonList& pl) {
    std::cout << "[";
    for (auto p : pl) {
        std::cout << *p << ",";
    }
    std::cout << "]" << std::endl;
}

int main() {
    LinkedBinaryTree<int> tree;
    tree.addRoot();
    *tree.root() = 4;
    tree.expandExternal(tree.root());
    *tree.root().left() = 2;
    *tree.root().right() = 6;
    
    printBT<int>(tree.positions());

    tree.expandExternal(tree.root().left());
    *tree.root().left().left() = 1;
    *tree.root().left().right() = 3;

    printBT<int>(tree.positions());

    tree.expandExternal(tree.root().right());
    *tree.root().right().left() = 5;
    *tree.root().right().right() = 7;

    printBT<int>(tree.positions());

    tree.removeAboveExternal(tree.root().left().right());

    printBT<int>(tree.positions());

    return 0;
}
