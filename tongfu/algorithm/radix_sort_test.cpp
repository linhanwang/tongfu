#include "tongfu/algorithm/radix_sort.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <climits>

using namespace tongfu;

int main() {
    {
        std::vector<int> keys = {41324, 3241, 14123, 32141, 12, 12341324, 234};

        RadixSort::radixSort(keys);

        for (int c : keys) std::cout << c << ",";
        std::cout << std::endl;
    }

    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, INT_MAX - 1);

        std::vector<int> keys;
        for (int i = 0; i < 1024; ++i) {
            int v = distrib(gen);
            keys.push_back(v);
        }

        RadixSort::radixSort(keys);

        std::cout << "keys should be sorted: "
                  << std::is_sorted(keys.begin(), keys.end()) << std::endl;
    }

    return 0;
}
