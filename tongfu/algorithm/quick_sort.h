#pragma once

#include <vector>

namespace tongfu {

class Quick {
   private:
    static int partition(std::vector<int>& a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        int v = a[lo];
        while (true) {
            while (a[++i] < v) {
                if (i == hi) break;
            }

            while (a[--j] > v) {
                if (j == lo) break;  // redundant since a[lo] acts as sentinel
            }

            if (i >= j) break;

            std::swap(a[i], a[j]);
        }
        std::swap(a[lo], a[j]);
        return j;
    }

    static void sort(std::vector<int>& a, int lo, int hi) {
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
    }

   public:
    static void sort(std::vector<int>& a) {
        // todo: shuffle a
        sort(a, 0, a.size() - 1);
    }

    static int select(std::vector<int>& a, int k) {
        // todo: shuffle
        int lo = 0, hi = a.size() - 1;
        while (hi > lo) {
            int i = partition(a, lo, hi);
            if (i > k)
                hi = i - 1;
            else if (i < k)
                lo = i + 1;
            else
                return a[i];
        }
        return a[lo];
    }
};

}  // namespace tongfu
