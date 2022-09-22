#include "tongfu/algorithm/quick_sort.h"
#include <iostream>
#include <vector>

using namespace tongfu;

int main() {
    {
        std::vector<int> a = {2, 3, 9, 4, 1, 5, 8, 7, 6, 3};

        Quick::sort(a);

        for (int i : a) {
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }

    {
        std::vector<int> a = {2, 3, 9, 4, 1, 5, 8, 7, 6, 3};

        std::cout << "3rd smallest: " << Quick::select(a, 3) << std::endl;
    }

    return 0;
}
