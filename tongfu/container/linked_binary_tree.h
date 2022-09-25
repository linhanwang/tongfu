#pragma once

#include <list>
#include <cassert>

namespace tongfu {

template <typename E>
class LinkedBinaryTree {
   protected:
    struct Node {
        E elem;
        Node* parent;
        Node* left;
        Node* right;
        Node() : elem(), parent(nullptr), left(nullptr), right(nullptr) {}
    };

   public:
    class Position {
       private:
        Node* node;

       public:
        Position(Node* n = nullptr) : node(n) {}
        E& operator*() { return node->elem; }
        const E& operator*() const { return node->elem; }
        bool operator==(const Position& p) const { return node == p.node; }
        bool operator!=(const Position& p) const { return node != p.node; }
        Position left() const { return Position(node->left); }
        Position right() const { return Position(node->right); }
        Position parent() const { return Position(node->parent); }
        bool isRoot() const { return node->parent == nullptr; }
        bool isExternal() const {
            return (node->left == nullptr) && (node->right == nullptr);
        }

        bool isInternal() const {
            return !isExternal();
        }

        friend class LinkedBinaryTree<E>;
    };

    using PositonList = std::list<Position>;

   public:
    LinkedBinaryTree();
    int size() const;
    bool empty() const;
    Position root() const;
    PositonList positions() const;
    void addRoot();
    void expandExternal(const Position& p);
    Position removeAboveExternal(const Position& p);
    Position restructure(const Position& p);
    void rotate(const Position& p);

   protected:
    void preorder(Node* n, PositonList& pl) const;
    void relink(Node* parent, Node* child, bool makeLeftChild);

   private:
    Node* _root;
    int n;
};

template <typename E>
LinkedBinaryTree<E>::LinkedBinaryTree() : _root(nullptr), n(0) {}

template <typename E>
int LinkedBinaryTree<E>::size() const {
    return n;
}

template <typename E>
bool LinkedBinaryTree<E>::empty() const {
    return size() == 0;
}

template <typename E>
typename LinkedBinaryTree<E>::Position LinkedBinaryTree<E>::root() const {
    return Position(_root);
}

template <typename E>
void LinkedBinaryTree<E>::addRoot() {
    _root = new Node;
    n = 1;
}

template <typename E>
void LinkedBinaryTree<E>::expandExternal(const Position& p) {
    p.node->left = new Node;
    p.node->left->parent = p.node;
    p.node->right = new Node;
    p.node->right->parent = p.node;
    n += 2;
}

/*
 * remove a external node and its parent
 * */
template <typename E>
typename LinkedBinaryTree<E>::Position LinkedBinaryTree<E>::removeAboveExternal(
    const Position& p) {
    auto parent = p.node->parent;
    auto sib = (p.node == parent->left) ? parent->right : parent->left;
    if (parent == _root) {
        _root = sib;
        sib->parent = nullptr;
    } else {
        auto gparent = parent->parent;
        if (parent == gparent->left)
            gparent->left = sib;
        else
            gparent->right = sib;

        sib->parent = gparent;
    }
    delete p.node;
    delete parent;
    return Position(sib);
}

template <typename E>
typename LinkedBinaryTree<E>::PositonList LinkedBinaryTree<E>::positions()
    const {
    PositonList pl;
    preorder(_root, pl);
    return pl;
}

template <typename E>
void LinkedBinaryTree<E>::preorder(Node* n, PositonList& pl) const {
    if (n == nullptr) return;

    pl.push_back(n);

    preorder(n->left, pl);
    preorder(n->right, pl);
}

template<typename E>
void LinkedBinaryTree<E>::relink(Node* parent, Node* child, bool makeLeftChild) {
    child->parent = parent;
    if (makeLeftChild) parent->left = child;
    else parent->right = child;
}

template<typename E>
void LinkedBinaryTree<E>::rotate(const Position& p) {
    assert(p.node);
    assert(p.node->parent);

    Node* x = p.node;
    Node* y = x->parent;                    // we assume this exists
    Node* z = y->parent;                    // grandparent (possibley null)
    if (z == nullptr) {
        _root = x;                          // x becomes root of the tree
        x->parent = nullptr;
    } else {
        relink(z, x, y == z->left);         // x becomes direct child of z
    }

    // now rotate x and y, including transfer of middle subtree
    if (x == y->left) {
        relink(y, x->right, true);        // x's right child becomes y's left
        relink(x, y, false);              // y becomes x's right child
    } else {
        relink(y, x->left, false);        // x's left becomes y's left
        relink(x, y, true);               // y becomes left child of x
    }
}

template <typename E>
typename LinkedBinaryTree<E>::Position LinkedBinaryTree<E>::restructure(
    const Position& x) {
    Position y = x.parent();
    Position z = y.parent();
    if ((x == y.right()) == (y == z.right())) { // matching alignments
        rotate(y);                              // single rotation(of y)
        return y;                               // y is new subtree root
    } else {                                    // opposite alignments
        rotate(x);                              // double rotation (of x)
        rotate(x);
        return x;                               // x is new subtree root
    }
}

}  // namespace tongfu
