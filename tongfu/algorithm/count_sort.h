#pragma once

#include <algorithm>
#include <vector>

namespace tongfu {

class CountingSort {
   public:
    static void countingSort(std::vector<int>& keys) {
        auto minMax = std::minmax_element(keys.begin(), keys.end());
        int minNum = *minMax.first;
        int maxNum = *minMax.second;
        std::vector<int> counts(maxNum - minNum + 2, 0);
        for (int num : keys) {
            counts[num - minNum + 1]++;
        }

        for (int i = 0; i < counts.size() - 1; ++i) {
            counts[i + 1] += counts[i];
        }

        std::vector<int> aux(keys.size(), 0);
        for (int num : keys) {
            aux[counts[num - minNum]++] = num;
        }
        std::swap(keys, aux);
    }
};

}  // namespace tongfu
