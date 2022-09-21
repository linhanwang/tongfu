#include "tongfu/container/doubly_linked_list.h"
#include "tongfu/container/search_tree.h"
#include <cassert>
#include <ostream>

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

    template<typename X, typename Y>
    friend std::ostream& operator<<(std::ostream&, const RBEntry<X, Y>&);
};

template<typename X, typename Y>
inline std::ostream& operator<<(std::ostream& out, const RBEntry<X, Y>& e) {
    if (e.isRed()) {
        out << "R";
    } else {
        out << "B";
    }
    out << e.key();
    return out;
}

template<typename K, typename V>
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
        TPos r = ST::eraser(u);
        if ((r == ST::root()) || (*r).isRed() || wasParentRed(r))
            setBlack(r);
        else {
            TPos sib = sibling(r);
            if (sib.isInternal() && ((*sib).isBlack() || sib.left().isInternal()))
                remedyDoubleBlack(r);
        }
    }
protected:
    void remedyDoubleRed(const TPos& z) {
        TPos v = z.parent();
        if (v == ST::root() || (*v).isBlack()) return;

        if ((*sibling(v)).isBlack()) { // Case 1: restructuring
            v = ST::restructure(z);
            setBlack(v);
            setRed(v.left());
            setRed(v.right());
        } else {                       // Case 2: recoloring
            setBlack(v);
            setBlack(sibling(v));
            TPos u = v.parent();
            if (u == ST::root()) return;
            setRed(u);
            remedyDoubleRed(u);        // may need to fix u now
        }
    }

    void remedyDoubleBlack(const TPos& r) {
        TPos x = r.parent();
        TPos y = sibling(r);
        if ((*y).isBlack()) {
            if ((*y.left()).isRed() || (*y.right()).isRed()) { // Case 1: restructuring
                TPos z = (*y.left()).isRed() ? y.left() : y.right();
                Color topColor = (*x).color();
                z = ST::restructure(z);
                setColor(z, topColor);
                setBlack(r);
                setBlack(z.left());
                setBlack(z.right());
            } else {                             // Case 2: recoloring
                setBlack(r);
                setRed(y);
                if ((*x).isBlack() && (x != ST::root()))
                    remedyDoubleBlack(x);
                setBlack(x);
            }
        } else {                                 // Case 3: adjustment
            ST::rotate(y);
            setBlack(y);
            setBlack(x);
            remedyDoubleBlack(r);
        }
    }

    bool wasParentRed(const TPos& p) {
        return (*p.parent()).isRed();
    }

    TPos sibling(const TPos& p) {
        TPos parent = p.parent();
        if (p == ST::root()) return TPos(nullptr);
        if (p == parent.left())
            return parent.right();
        else
            return parent.left();
    }

    void setBlack(TPos p) {
        (*p).setColor(BLACK);
    }

    void setRed(TPos p) {
        (*p).setColor(RED);
    }

    void setColor(TPos p, Color c) {
        (*p).setColor(c);
    }
};

}  // namespace tongfu
