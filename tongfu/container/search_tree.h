#include <cassert>

#include "tongfu/container/entry.h"
#include "tongfu/container/linked_binary_tree.h"

namespace tongfu {

template <typename K, typename V>
class SearchTree {
   public:
    using E = tongfu::Entry<K, V>;
    class Iterator;

   public:
    SearchTree();
    int size() const { return n; }
    bool empty() const { return size() == 0; }
    Iterator find(const K& k);
    Iterator insert(const K& k, const V& v);
    void erase(const K& k);
    void erase(const Iterator& p);
    Iterator begin();
    Iterator end();

   protected:
    using BinaryTree = LinkedBinaryTree<E>;
    using TPos = typename BinaryTree::Position;
    TPos root() const;
    TPos finder(const K& k, const TPos& v);
    TPos inserter(const K& k, const V& v);
    TPos eraser(TPos& v);
    TPos restructure(const TPos& v);

   private:
    BinaryTree T;
    int n;

   public:
    class Iterator {
       private:
        TPos v;

       public:
        Iterator(const TPos& vv) : v(vv) {}
        const E& operator*() const { return *v; }
        E& operator*() { return *v; }
        bool operator==(const Iterator& p) const { return v == p.v; }
        bool operator!=(const Iterator& p) const { return v != p.v; }
        Iterator& operator++();
        friend class SearchTree<K, V>;
    };
};

template <typename K, typename V>
typename SearchTree<K, V>::Iterator& SearchTree<K, V>::Iterator::operator++() {
    TPos w = v.right();
    if (w.isInternal()) {
        do {
            v = w;
            w = w.left();
        } while (w.isInternal());
    } else {
        w = v.parent();
        while (v == w.right()) {
            v = w;
            w = w.parent();
        }
        v = w;
    }
    return *this;
}

template <typename K, typename V>
SearchTree<K, V>::SearchTree() : T(), n(0) {
    T.addRoot();  // create the super root
    T.expandExternal(T.root());
}

/*
 * get virtual root
 * */
template <typename K, typename V>
typename SearchTree<K, V>::TPos SearchTree<K, V>::root() const {
    return T.root().left();
}

template <typename K, typename V>
typename SearchTree<K, V>::Iterator SearchTree<K, V>::begin() {
    TPos v = root();
    while (v.isInternal()) v = v.left();
    return Iterator(v.parent());
}

template <typename K, typename V>
typename SearchTree<K, V>::Iterator SearchTree<K, V>::end() {
    return Iterator(T.root());
}

template <typename K, typename V>
typename SearchTree<K, V>::TPos SearchTree<K, V>::finder(const K& k,
                                                         const TPos& v) {
    if (v.isExternal()) return v;
    if (k < (*v).key())
        return finder(k, v.left());
    else if ((*v).key() < k)
        return finder(k, v.right());
    else
        return v;
}

template <typename K, typename V>
typename SearchTree<K, V>::Iterator SearchTree<K, V>::find(const K& k) {
    TPos v = finder(k, root());
    if (v.isInternal())
        return Iterator(v);
    else
        return end();
}

template <typename K, typename V>
typename SearchTree<K, V>::TPos SearchTree<K, V>::inserter(const K& k,
                                                           const V& x) {
    TPos v = finder(k, root());
    while (v.isInternal())  // we allow duplicate keys
        v = finder(k, v.right());
    T.expandExternal(v);
    (*v).setKey(k);
    (*v).setValue(x);
    n++;
    return v;
}

template <typename K, typename V>
typename SearchTree<K, V>::Iterator SearchTree<K, V>::insert(const K& k,
                                                             const V& x) {
    TPos v = inserter(k, x);
    return Iterator(v);
}

template <typename K, typename V>
typename SearchTree<K, V>::TPos SearchTree<K, V>::eraser(TPos& v) {
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
        (*v).setKey((*u).key());
        (*v).setValue((*u).value());
    }
    n--;
    return T.removeAboveExternal(w);
}

template <typename K, typename V>
void SearchTree<K, V>::erase(const K& k) {
    TPos v = finder(k, root());
    assert(!v.isExternal());
    eraser(v);
}

template <typename K, typename V>
void SearchTree<K, V>::erase(const Iterator& p) {
    erase(p.v);
}

}  // namespace tongfu
