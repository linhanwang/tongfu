#include <string>
#include <vector>

namespace tongfu {

class MSD {
   private:
    static constexpr int R = 256;
    static constexpr int CUTOFF = 15;

   public:
    static void sort(std::vector<std::string>& a) {
        int n = a.size();
        std::vector<std::string> aux(n);
        sort(a, 0, n - 1, 0, aux);
    }

   private:
    static int charAt(std::string& s, int d) {
        if (d == s.size()) return -1;
        return s[d];
    }

    static bool less(std::string& v, std::string& w, int d) {
        for (int i = d; i < std::min(v.size(), w.size()); ++i) {
            if (v[i] < w[i]) return true;
            if (v[i] > w[i]) return false;
        }
        return v.size() < w.size();
    }

    static void insertion(std::vector<std::string>& a, int lo, int hi, int d) {
        for (int i = lo; i <= hi; ++i)
            for (int j = i; j > lo && less(a[j], a[j - 1], d); --j)
                std::swap(a[j], a[j - 1]);
    }

    static void sort(std::vector<std::string>& a, int lo, int hi, int d,
                     std::vector<std::string>& aux) {
        // cutoff to insertion sort for small subarrays
        if (hi <= lo + CUTOFF) {
            insertion(a, lo, hi, d);
            return;
        }

        // compute frequeny counts
        std::vector<int> count(R + 2);
        for (int i = lo; i <= hi; i++) {
            int c = charAt(a[i], d);
            count[c + 2]++;
        }

        // transform counts to indices
        for (int r = 0; r < R + 1; ++r) count[r + 1] += count[r];

        // distribute
        for (int i = lo; i <= hi; ++i) {
            int c = charAt(a[i], d);
            aux[count[c + 1]++] = a[i];
        }
        
        // copy back
        for (int i = lo; i <= hi; ++i) a[i] = aux[i - lo];

        // recursively sort for each character (excludes sentinel -1)
        for (int r = 0; r < R; r++)
            sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
    }
};

}  // namespace tongfu
