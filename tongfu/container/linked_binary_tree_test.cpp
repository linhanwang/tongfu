#include "tongfu/container/linked_binary_tree.h"
#include <iostream>

using namespace tongfu;

/*
 * preorder sequence with E as external node can represent a tree uniquely.
 * */
template<typename E>
void printBT(const typename LinkedBinaryTree<E>::PositonList& pl) {
    std::cout << "[";
    for (auto p : pl) {
        if (p.isExternal()) std::cout << "E";
        else std::cout << *p;
        std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

template<typename E>
void printBTWithExternal(const typename LinkedBinaryTree<E>::PositonList& pl) {
    std::cout << "[";
    for (auto p : pl) {
        std::cout << *p << ",";
    }
    std::cout << "]" << std::endl;
}


int main() {
    {
        std::cout << "basic tests: " << std::endl;
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
    }

    {
        std::cout << "rotation test: " << std::endl;
        std::cout << "single rotation: " << std::endl;
        LinkedBinaryTree<int> tree;
        tree.addRoot();
        *tree.root() = 2;
        
        tree.expandExternal(tree.root());
        *tree.root().left() = 1;
        *tree.root().right() = 4;

        tree.expandExternal(tree.root().right());
        *tree.root().right().left() = 3;
        *tree.root().right().right() = 6;

        tree.expandExternal(tree.root().right().right());
        *tree.root().right().right().left() = 5;
        *tree.root().right().right().right() = 7;

        printBTWithExternal<int>(tree.positions());

        tree.restructure(tree.root().right().right());
        
        printBTWithExternal<int>(tree.positions());
    }

    {
        std::cout << "double rotation: " << std::endl;
        LinkedBinaryTree<int> tree;
        tree.addRoot();
        *tree.root() = 2;

        tree.expandExternal(tree.root());
        *tree.root().left() = 1;
        *tree.root().right() = 6;

        tree.expandExternal(tree.root().right());
        *tree.root().right().left() = 4;
        *tree.root().right().right() = 7;

        tree.expandExternal(tree.root().right().left());
        *tree.root().right().left().left() = 3;
        *tree.root().right().left().right() = 5;

        printBTWithExternal<int>(tree.positions());

        tree.restructure(tree.root().right().left());

        printBTWithExternal<int>(tree.positions());
    }

    return 0;
}
