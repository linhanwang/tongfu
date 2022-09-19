#include "tongfu/container/hash_map.h"
#include <functional>
#include <iostream>

using namespace tongfu;

int main() {
    HashMap<int, int, std::hash<int>> dict;
    
    dict.put(1, 1);
    std::cout << "size should be 1: " << dict.size() << std::endl;
    
    dict.put(2, 2);

    std::cout << "find(1) should be 1: " << (*dict.find(1)).value() << std::endl;

    dict.put(3, 3);
    dict.put(4, 4);
    dict.put(5, 5);
    
    std::cout << "find(3) should be 3: " << (*dict.find(1)).value() << std::endl;
    
    dict.put(3, 9);

    std::cout << "find(3) should be 9: " << (*dict.find(3)).value() << std::endl;
    std::cout << "size should be 5: " << dict.size() << std::endl;
   
    auto iter = dict.begin();
    while (iter != dict.end()) {
        std::cout << (*iter).key() << " : " << (*iter).value() << std::endl;
        ++iter; // only ++iter is supported, not iter++
    }

    return 0;
}
