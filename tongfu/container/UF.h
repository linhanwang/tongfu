#pragma once

#include <vector>

namespace tongfu {

class UF {
   public:
    UF(int n) : count_(n), arr(n, -1) {}

    void Union(int x1, int x2) {
        int root1 = find(x1);
        int root2 = find(x2);
        if (root1 == root2) return;

        if (arr[root2] < arr[root1]) {
            arr[root2] += arr[root1];
            arr[root1] = root2;
        } else {
            arr[root1] += arr[root2];
            arr[root2] = root1;
        }
        --count_;
    }

    int find(int x) {
        if (arr[x] < 0) {
            return x;
        } else {
            arr[x] = find(arr[x]);
            return arr[x];
        }
    }

    bool connected(int p, int q) { return find(p) == find(q); }

    int count() const { return count_; }

   private:
    std::vector<int> arr;
    int count_;
};

}  // namespace tongfu
