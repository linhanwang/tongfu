#include "tongfu/container/avl_tree.h"

#include <iostream>
#include <random>
#include <vector>

using namespace tongfu;

int main() {
    {
        std::cout << "Binary search tree tests:" << std::endl;
        AVLTree<int, int> tree;

        tree.insert(1, 1);

        std::cout << "size should be 1: " << tree.size() << std::endl;

        tree.insert(2, 2);
        tree.insert(6, 6);
        tree.insert(4, 4);
        tree.insert(3, 3);
        tree.insert(3, 6);
        tree.insert(5, 5);

        std::cout << "size should be 7: " << tree.size() << std::endl;

        auto iter = tree.begin();
        while (iter != tree.end()) {
            std::cout << (*iter).key() << " : " << (*iter).value() << std::endl;
            ++iter;
        }

        std::cout << "find(3) should be 3: " << (*tree.find(3)).value()
                  << std::endl;

        tree.erase(2);
        tree.erase(4);

        std::cout << "size should be 5: " << tree.size() << std::endl;
        std::cout << "find(3) should be 3: " << (*tree.find(3)).value()
                  << std::endl;

        tree.erase(3);
        std::cout << "find(3) should be 6: " << (*tree.find(3)).value()
                  << std::endl;
    }

    {
        std::cout << "AVL tree tests: " << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 1000);

        AVLTree<int, int> tree;
        std::vector<int> keys;
        for (int i = 0; i < 128; ++i) {
            int v = distrib(gen);
            keys.push_back(v);
        }

        for (auto key : keys) {
            tree.insert(key, key);
        }

        tree.debug();

        for (auto key : keys) {
            if (key % 2 == 0) tree.erase(key);
        }

        tree.debug();

        for (auto key : keys) {
            if (key % 2 == 1) {
                assert((*tree.find(key)).value() == key);
            }
        }
    }

    return 0;
}
