#pragma once

#include <vector>

namespace tongfu {

template <typename E>
class VectorCompleteTree {
   private:
    std::vector<E> V;

   public:
    using Position = typename std::vector<E>::iterator;

   protected:
    Position pos(int i) { return V.begin() + i; }

    int idx(const Position& p) const { return p - V.begin(); }

   public:
    VectorCompleteTree() : V(1) {}
    int size() const { return V.size() - 1; }
    Position left(const Position& p) { return pos(2 * idx(p)); }
    Position right(const Position& p) { return pos(2 * idx(p) + 1); }
    Position parent(const Position& p) { return pos(idx(p) / 2); }
    bool hasLeft(const Position& p) { return 2 * idx(p) <= size(); }
    bool hasRight(const Position& p) { return 2 * idx(p) + 1 <= size(); }
    bool isRoot(const Position& p) { return idx(p) == 1; }
    Position root() { return pos(1); }
    Position last() { return pos(size()); }
    void addLast(const E& e) { V.push_back(e); }
    void removeLast() { V.pop_back(); }
    void swap(const Position& p, const Position& q) { std::swap(*p, *q); }
};

template <typename E, typename C>
class HeapPriorityQueue {
   public:
    int size() const;
    bool empty() const;
    void insert(const E& e);
    const E& min();
    void removeMin();

   private:
    VectorCompleteTree<E> T;
    C isLess;

    using Position = typename VectorCompleteTree<E>::Position;
};

template <typename E, typename C>
int HeapPriorityQueue<E, C>::size() const {
    return T.size();
}

template <typename E, typename C>
bool HeapPriorityQueue<E, C>::empty() const {
    return size() == 0;
}

template <typename E, typename C>
const E& HeapPriorityQueue<E, C>::min() {
    return *(T.root());
}

template <typename E, typename C>
void HeapPriorityQueue<E, C>::insert(const E& e) {
    T.addLast(e);
    Position node = T.last(); // upheap
    while (!T.isRoot(node)) {
        Position p = T.parent(node);
        if (!isLess(*node, *p)) break;
        T.swap(node, p);
        node = p;
    }
}

template <typename E, typename C>
void HeapPriorityQueue<E, C>::removeMin() {
    if (size() == 1)
        T.removeLast();
    else {
        Position p = T.root(); // downheap
        T.swap(p, T.last());
        T.removeLast();
        while (T.hasLeft(p)) {
            Position c = T.left(p);
            if (T.hasRight(p) && isLess(*(T.right(p)), *c)) c = T.right(p);
            if (!isLess(*c, *p)) break;
            T.swap(p, c);
        }
    }
}

}  // namespace tongfu
