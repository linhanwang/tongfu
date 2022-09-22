#include "tongfu/algorithm/merge_sort.h"
#include <iostream>
#include <vector>

using namespace tongfu;

int main() {
    {
        std::vector<int> a = {4, 2, 6, 9, 1, 7, 8, 2};
    
        Merge::sort(a);
    
        for (int i : a) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> a = {4, 2, 6, 9, 1, 7, 8, 2};
    
        MergeBU::sort(a);
    
        for (int i : a) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }

    return 0;
}
