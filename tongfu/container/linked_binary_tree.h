#include <list>

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
        Position(Node* n) : node(n) {}
        E& operator*() { return node->elem; }
        Position left() const { return Position(node->left); }
        Position right() const { return Position(node->right); }
        Position parent() const { return Position(node->parent); }
        bool isRoot() const { return node->parent == nullptr; }
        bool isExternal() const {
            return (node->left == nullptr) && (node->right == nullptr);
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

   protected:
    void preorder(Node* n, PositonList& pl) const;

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

}  // namespace tongfu
