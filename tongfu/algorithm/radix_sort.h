#pragma once

#include <array>
#include <vector>

namespace tongfu {

class RadixSort {
   private:
    static void countingSort(std::vector<int>& keys, std::vector<int>& aux,
                             int whichDigit) {
        std::vector<int> counts(16, 0);
        int shift = whichDigit * 4;
        for (int i = 0; i < keys.size(); ++i) {
            int num = (keys[i] >> shift) & 0xf;
            counts[num]++;
        }

        int total = 0;
        for (int i = 0; i < 16; ++i) {
            int c = counts[i];
            counts[i] = total;
            total = total + c;
        }

        for (int i = 0; i < keys.size(); ++i) {
            int num = (keys[i] >> shift) & 0xf;
            aux[counts[num]] = keys[i];
            counts[num]++;
        }
        std::swap(keys, aux);
    }

   public:
    static void radixSort(std::vector<int>& keys) {
        std::vector<int> aux(keys.size(), 0);
        for (int i = 0; i <= 7; ++i) {
            countingSort(keys, aux, i);
        }
    }
};

}  // namespace tongfu
