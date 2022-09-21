#include "tongfu/container/rb_tree.h"

#include <iostream>
#include <vector>
#include <random>

using namespace tongfu;

int main() {
    {
        std::cout << "Binary search tree tests:" << std::endl;
        RBTree<int, int> tree;

        tree.insert(1, 1);

        std::cout << "size should be 1: " << tree.size() << std::endl;

        tree.insert(2, 2);
        tree.insert(6, 6);
        tree.insert(4, 4);
        tree.insert(3, 3);
        tree.insert(3, 6);
        tree.insert(5, 5);

        tree.printBTWithExternal(); 

        std::cout << "size should be 7: " << tree.size() << std::endl;

        auto iter = tree.begin();
        while (iter != tree.end()) {
            std::cout << (*iter).key() << " : " << (*iter).value() << std::endl;
            ++iter;
        }

        std::cout << "find(3) should be 3 or 6: " << (*tree.find(3)).value()
                  << std::endl;

        tree.erase(2);
        tree.printBTWithExternal(); 
        tree.erase(4);
        tree.printBTWithExternal(); 

        std::cout << "size should be 5: " << tree.size() << std::endl;
        std::cout << "find(3) should be 3 or 6: " << (*tree.find(3)).value()
                  << std::endl;

        tree.erase(3);
        std::cout << "find(3) should be 3 or 6: " << (*tree.find(3)).value()
                  << std::endl;
        std::cout << "find(5) should be 5: " << (*tree.find(5)).value()
                  << std::endl;
    }
    
    {
        std::cout << "RB tree tests: " << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 10000);

        RBTree<int, int> tree;
        std::vector<int> keys;
        for (int i = 0; i < 1024; ++i) {
            int v = distrib(gen);
            keys.push_back(v);
        }

        for (auto key : keys) {
            tree.insert(key, key);
        }


        for (auto key : keys) {
            if (key % 2 == 0) tree.erase(key);
        }


        for (auto key : keys) {
            if (key % 2 == 1) {
                assert((*tree.find(key)).value() == key);
            }
        }
    }

    return 0;
}
