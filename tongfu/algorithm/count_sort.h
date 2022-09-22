#include <algorithm>
#include <vector>

namespace tongfu {

class CountingSort {
    public:
        static void countingSort(std::vector<int>& keys) {
            auto minMax = std::minmax_element(keys.begin(), keys.end());
            int minNum = *minMax.first;
            int maxNum = *minMax.second;
            std::vector<int> counts(maxNum - minNum + 1, 0);
            for (int num : keys) {
                counts[num - minNum]++;
            }

            int total = 0;
            for (int i = 0; i < counts.size(); ++i) {
                int c = counts[i];
                counts[i] = total;
                total = total + c;
            }

            std::vector<int> aux(keys.size(), 0);
            for (int num : keys) {
                aux[counts[num - minNum]] = num;
                counts[num - minNum]++;
            }
            std::swap(keys, aux);
        }
};

}
