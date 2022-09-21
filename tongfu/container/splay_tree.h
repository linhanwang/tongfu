#include <algorithm>
#include <iostream>
#include "tongfu/container/search_tree.h"

namespace tongfu {

template<typename K, typename V>
class SplayTree : public SearchTree<K, V> {
public:
    using Entry = tongfu::Entry<K, V>;
    using Iterator = typename SearchTree<K, V>::Iterator;
protected:
    using ST = SearchTree<K, V>;
    using TPos = typename ST::TPos;
public:
    Iterator find(const K& k) {
        TPos p = ST::finder(k, ST::root());
        rebalanceAccess(p);
        return p.isExternal() ? ST::end() : Iterator(p);
    }

    Iterator insert(const K& k, const V& v) {
        TPos p = ST::inserter(k, v);
        rebalanceInsert(p);
        return Iterator(p);
    }

    void erase(const K& k) {
        TPos p = ST::finder(k, ST::root());
        assert(p.isInternal());
        TPos n = ST::eraser(p);
        rebalanceDelete(n);
    }

    void erase(const Iterator& p) {
        erase(p);
    }

    void debug() {
        std::cout << "size: " << ST::size() << " height: " << height(ST::root())
            << std::endl;
    }
private:
    int height(const TPos& v) {
        if (v.isExternal()) return 0;
        return 1 + std::max(height(v.left()), height(v.right()));
    }

    void splay(const TPos& p) {
        while (p != ST::root()) {
            TPos parent = p.parent();
            TPos grant = parent.parent();
            if (parent == ST::root()) {
                ST::rotate(p);               // zig case
            } else if ((parent == grant.left()) == (p == parent.left())) {
                ST::rotate(parent);          // zig-zig case
                ST::rotate(p);
            } else {
                ST::rotate(p);               // zig-zag case
                ST::rotate(p);
            }
        }
    }

    void rebalanceAccess(const TPos& p) {
        if (p.isExternal()) {
            if (p.parent() != ST::root())
                splay(p.parent());
        } else {
            splay(p);
        } 
    }

    void rebalanceInsert(const TPos& p) {
        splay(p);
    }

    void rebalanceDelete(const TPos& p) {
        if (p != ST::root()) splay(p.parent());
    }
};

}
