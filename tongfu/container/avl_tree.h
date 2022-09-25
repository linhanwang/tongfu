#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

#include "tongfu/container/search_tree.h"

namespace tongfu {

template <typename K, typename V>
class AVLTree;

template <typename K, typename V>
class AVLEntry : public Entry<K, V> {
   private:
    int ht;

   protected:
    int height() const { return ht; }
    void setHeight(int h) { ht = h; }

   public:
    AVLEntry(const K& k = K(), const V& v = V()) : Entry<K, V>(k, v), ht(0) {}

    friend class AVLTree<K, V>;
};

template <typename K, typename V>
class AVLTree : public SearchTree<K, V, AVLEntry<K, V>> {
   public:
    using AVLEntry = tongfu::AVLEntry<K, V>;
    using Iterator = typename SearchTree<K, V, AVLEntry>::Iterator;

   protected:
    using ST = SearchTree<K, V, AVLEntry>;
    using TPos = typename ST::TPos;

   public:
    AVLTree();
    Iterator insert(const K& k, const V& x);
    void erase(const K& k);
    void debug() {
        std::cout << "size: " << ST::size() << " height: " << height(ST::root())
                  << std::endl;
        std::cout << "IsBalanced Tree: " << isBalancedTree(ST::root())
                  << std::endl;
    }

   protected:
    int height(const TPos& v) const;
    void setHeight(TPos v);
    bool isBalanced(const TPos& v) const;
    TPos tallGrandchild(const TPos& v) const;
    void rebalance(const TPos& v);
    bool isBalancedTree(const TPos& v) const {
        if (v.isExternal()) return true;

        if (!isBalanced(v)) return false;
        if (!isBalancedTree(v.left())) return false;
        if (!isBalancedTree(v.right())) return false;

        return true;
    }
};

template <typename K, typename V>
AVLTree<K, V>::AVLTree() : ST() {}

template <typename K, typename V>
int AVLTree<K, V>::height(const TPos& v) const {
    return v.isExternal() ? 0 : (*v).height();
}

template <typename K, typename V>
void AVLTree<K, V>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));
}

template <typename K, typename V>
bool AVLTree<K, V>::isBalanced(const TPos& v) const {
    int bal = height(v.left()) - height(v.right());
    return std::abs(bal) <= 1;
}

template <typename K, typename V>
typename AVLTree<K, V>::TPos AVLTree<K, V>::tallGrandchild(
    const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr)) {
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
    } else {
        if (height(zr.right()) >= height(zr.left()))
            return zr.right();
        else
            return zr.left();
    }
}

template <typename K, typename V>
void AVLTree<K, V>::rebalance(const TPos& v) {
    TPos z = v;
    while (z != ST::root()) {
        z = z.parent();
        setHeight(z);
        if (!isBalanced(z)) {
            TPos x = tallGrandchild(z);
            z = ST::restructure(x);
            setHeight(z.left());
            setHeight(z.right());
            setHeight(z);
        }
    }
}

template <typename K, typename V>
typename AVLTree<K, V>::Iterator AVLTree<K, V>::insert(const K& k, const V& x) {
    TPos v = ST::inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
}

template <typename K, typename V>
void AVLTree<K, V>::erase(const K& k) {
    TPos v = ST::finder(k, ST::root());
    assert(Iterator(v) != ST::end());
    TPos w = ST::eraser(v);
    rebalance(w);
}

}  // namespace tongfu
