#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <utility>

#include "tongfu/container/doubly_linked_list.h"
#include "tongfu/container/search_tree.h"

namespace tongfu {

template <typename K, typename V>
class RBTree;

enum Color { RED, BLACK };

template <typename K, typename V>
class RBEntry : public Entry<K, V> {
   private:
    Color col;

   protected:
    Color color() const { return col; }
    bool isRed() const { return col == RED; }
    bool isBlack() const { return col == BLACK; }
    void setColor(Color c) { col = c; }

   public:
    RBEntry(const K& k = K(), const V& v = V())
        : Entry<K, V>(k, v), col(BLACK) {}
    friend class RBTree<K, V>;

    template <typename X, typename Y>
    friend std::ostream& operator<<(std::ostream&, const RBEntry<X, Y>&);
};

template <typename X, typename Y>
inline std::ostream& operator<<(std::ostream& out, const RBEntry<X, Y>& e) {
    if (e.isRed()) {
        out << "R";
    } else {
        out << "B";
    }
    out << e.key();
    return out;
}

template <typename K, typename V>
class RBTree : public SearchTree<K, V, RBEntry<K, V>> {
   public:
    using RBEntry = tongfu::RBEntry<K, V>;
    using Iterator = typename SearchTree<K, V, RBEntry>::Iterator;

   protected:
    using ST = SearchTree<K, V, RBEntry>;
    using TPos = typename ST::TPos;

   public:
    Iterator insert(const K& k, const V& x) {
        TPos v = ST::inserter(k, x);
        if (v == ST::root()) {
            setBlack(v);
        } else {
            setRed(v);
            remedyDoubleRed(v);
        }
        return Iterator(v);
    }

    void erase(const K& k) {
        TPos u = ST::finder(k, ST::root());
        assert(Iterator(u) != ST::end());
        auto item = rbEraser(u);
        TPos r = item.first;
        Color col = item.second;
        if (col == RED) return;

        if ((*r).isRed())  // deleted parent was black
            setBlack(r);   // so this restores black depth
        else {
            if (!r.isExternal()) {
                std::cout << "deleted node color isRed: " << (col == RED)
                          << std::endl;
                std::abort();
            }
            if (r == ST::root()) return;
            remedyDoubleBlack(r);
        }
    }

    std::pair<TPos, Color> rbEraser(TPos& v) {
        Color col = (*v).color();
        TPos w;
        if (v.left().isExternal())
            w = v.left();
        else if (v.right().isExternal())
            w = v.right();
        else {
            w = v.right();
            do {
                w = w.left();
            } while (w.isInternal());
            TPos u = w.parent();
            col = (*u).color();
            (*v).setKey((*u).key());
            (*v).setValue((*u).value());
        }
        ST::n--;
        return {ST::T.removeAboveExternal(w), col};
    }

    /* Ensure that current tree structure is valid RB tree (for debug only)*/
    bool sanityCheck() { return sanityRecurse(ST::root()) != -1; }

   protected:
    void remedyDoubleRed(const TPos& p) {
        TPos parent = p.parent();
        if ((*parent).isBlack()) return;

        TPos uncle = sibling(parent);
        if ((*uncle).isBlack()) {  // Case 1: restructuring
            TPos middle = ST::restructure(p);
            setBlack(middle);
            setRed(middle.left());
            setRed(middle.right());
        } else {  // Case 2: recoloring
            setBlack(parent);
            setBlack(uncle);
            TPos grand = parent.parent();
            if (grand == ST::root()) return;
            setRed(grand);
            remedyDoubleRed(grand);  // may need to fix u now
        }
    }

    void remedyDoubleBlack(const TPos& p) {
        TPos z = p.parent();
        TPos y = sibling(p);
        if ((*y).isBlack()) {
            if ((*y.left()).isRed() ||
                (*y.right()).isRed()) {  // Case 1: restructuring
                TPos x = (*y.left()).isRed() ? y.left() : y.right();
                Color topColor = (*z).color();
                TPos middle = ST::restructure(x);
                setColor(middle, topColor);
                setBlack(middle.left());
                setBlack(middle.right());
            } else {  // Case 2: recoloring
                setRed(y);
                if ((*z).isRed())
                    setBlack(z);
                else if (z != ST::root())
                    remedyDoubleBlack(z);
            }
        } else {  // Case 3: adjustment
            ST::rotate(y);
            setBlack(y);
            setRed(z);
            remedyDoubleBlack(p);
        }
    }

    /*
     * Returns black depth of subtree, if valid, or -1 if invalid
     * */
    int sanityRecurse(const TPos& p) {
        if (p.isExternal()) {
            if ((*p).isRed())
                return -1;
            else
                return 0;
        } else {
            if ((p == ST::root()) && (*p).isRed()) return -1;
            TPos left = p.left();
            TPos right = p.right();
            if ((*p).isRed() && ((*left).isRed() || (*right).isRed()))
                return -1;

            int a = sanityRecurse(left);
            if (a == -1) return -1;
            int b = sanityRecurse(right);
            if (a != b) return -1;

            return a + ((*p).isRed() ? 0 : 1);
        }
    }

    bool wasParentRed(const TPos& p) { return (*p.parent()).isRed(); }

    TPos sibling(const TPos& p) {
        TPos parent = p.parent();
        if (p == ST::root()) return TPos(nullptr);
        if (p == parent.left())
            return parent.right();
        else
            return parent.left();
    }

    void setBlack(TPos p) { (*p).setColor(BLACK); }

    void setRed(TPos p) { (*p).setColor(RED); }

    void setColor(TPos p, Color c) { (*p).setColor(c); }
};

}  // namespace tongfu
