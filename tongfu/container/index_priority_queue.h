#include <cassert>
#include <functional>
#include <vector>

namespace tongfu {

template <typename Key, typename Comp = std::less<Key>>
class IndexPQ {
   public:
    IndexPQ(int maxN)
        : maxN_(maxN),
          keys_(maxN_ + 1),
          pq_(maxN_ + 1),
          qp_(maxN_ + 1, -1),
          n_(0) {}

    bool isEmpty() const { return n_ == 0; }

    bool contains(int i) const { return qp_[i] != -1; }

    int size() const { return n_; }

    int topIndex() const { return pq_[1]; }

    Key topKey() const { return keys_[topIndex()]; }

    void pop() {
        assert(n_ > 0);
        int t = pq_[1];
        exch(1, n_--);
        sink(1);
        assert(t == pq_[n_ + 1]);
        qp_[t] = -1;
        pq_[n_ + 1] = -1;
    }

    void insert(int i, Key key) {
        assert(!contains(i));
        n_++;
        qp_[i] = n_;
        pq_[n_] = i;
        keys_[i] = key;
        swim(n_);
    }

    /*
     * Returns the key associated with index i
     * */
    Key keyOf(int i) const {
        assert(contains(i));
        return keys_[i];
    }

    /*
     * Change the key associated with index i to the specified value
     * */
    void changeKey(int i, Key key) {
        keys_[i] = key;
        swim(qp_[i]);
        sink(qp_[i]);
    }

    /*
     * Decrease the key associated with index i to the specified value
     * */
    void decreaseKey(int i, Key key) {
        assert(isLess_(keys_[i], key));
        keys_[i] = key;
        sink(qp_[i]);
    }

    /*
     * increase the key associated with index i to the specified value
     * */
    void increaseKey(int i, Key key) {
        assert(isLess_(key, keys_[i]));
        keys_[i] = key;
        swim(qp_[i]);
    }

    /*
     * Remove the key associated with index i
     * */
    void remove(int i) {
        int index = qp_[i];
        exch(index, n_--);
        swim(index);
        sink(index);
        qp_[i] = -1;
    }

   private:
    void swim(int k) {
        while (k > 1 && isLess(k / 2, k)) {
            exch(k, k / 2);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= n_) {
            int j = 2 * k;
            if (j < n_ && isLess(j, j + 1)) j++;
            if (!isLess(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

    bool isLess(int i, int j) { return isLess_(keys_[pq_[i]], keys_[pq_[j]]); }

    void exch(int i, int j) {
        int swap = pq_[i];
        pq_[i] = pq_[j];
        pq_[j] = swap;
        qp_[pq_[i]] = i;
        qp_[pq_[j]] = j;
    }

   private:
    int maxN_;
    int n_;
    std::vector<int> pq_;    // index of pq_ -> index
    std::vector<int> qp_;    // index -> index of pq_
    std::vector<Key> keys_;  // index -> key
    Comp isLess_;
};

}  // namespace tongfu
