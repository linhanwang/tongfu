#pragma once

#include <string>
#include <vector>

namespace tongfu {

class LSD {
   public:
    static void sort(std::vector<std::string>& a, int w) {
        int n = a.size();
        int R = 256;
        std::vector<std::string> aux(n);

        for (int d = w - 1; d >= 0; d--) {
            std::vector<int> count(R + 1, 0);
            for (int i = 0; i < n; ++i) count[a[i][d] + 1]++;

            for (int r = 0; r < R; ++r) count[r + 1] += count[r];

            for (int i = 0; i < n; ++i) aux[count[a[i][d]]++] = a[i];

            std::swap(a, aux);
        }
    }
};

}  // namespace tongfu
