#include <algorithm>
#include <vector>

namespace tongfu {

class Merge {
protected:
    static void merge(std::vector<int>& a, std::vector<int>& aux, int lo, int mid, int hi) {
        for (int k = lo; k <= hi; ++k) {
            aux[k] = a[k];
        }

        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; ++k) {
            if (i > mid)     a[k] = aux[j++];
            else if (j > hi) a[k] = aux[i++];
            else if (aux[j] < aux[i]) a[k] = aux[j++];
            else a[k] = aux[i++];
        }
    }

    static void sort(std::vector<int>& a, std::vector<int>& aux, int lo, int hi) {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid + 1, hi);
        merge(a, aux, lo, mid, hi);
    }

public:
    static void sort(std::vector<int>& a) {
        std::vector<int> aux(a.size(), 0);
        sort(a, aux, 0, a.size() - 1);
    }
};

class MergeBU : public Merge {
public:
    static void sort(std::vector<int>& a) {
        int n = a.size();
        std::vector<int> aux(n, 0);
        for (int len = 1; len < n; len*= 2) {
            for (int lo = 0; lo < n - len; lo += len + len) {
                int mid = lo + len - 1;
                int hi = std::min(lo+len+len-1, n - 1);
                merge(a, aux, lo, mid, hi);
            }
        }
    }
};

}
