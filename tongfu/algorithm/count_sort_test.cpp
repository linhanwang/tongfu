#include "tongfu/algorithm/count_sort.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace tongfu;

int main() {
    {
        std::vector<int> keys = {41324, 3241, 14123, 32141, 12, 12341324, 234};

        CountingSort::countingSort(keys);

        for (int c : keys) std::cout << c << ",";
        std::cout << std::endl;
    }

    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(-50000, 50000);

        std::vector<int> keys;
        for (int i = 0; i < 1024; ++i) {
            int v = distrib(gen);
            keys.push_back(v);
        }

        CountingSort::countingSort(keys);

        std::cout << "keys should be sorted: "
                  << std::is_sorted(keys.begin(), keys.end()) << std::endl;
    }

    return 0;
}
