#pragma once

namespace tongfu {

template <typename E>
class NodeList {
   private:
    struct Node {
        E elem;
        Node* prev;
        Node* next;
    };

   public:
    class Iterator {
       public:
        E& operator*();
        bool operator==(const Iterator& p) const;
        bool operator!=(const Iterator& p) const;
        Iterator& operator++();
        Iterator& operator--();
        friend class NodeList<E>;

       private:
        Node* v;
        Iterator(Node* u);
    };

   public:
    NodeList();
    int size() const;
    bool empty() const;
    Iterator begin() const;
    Iterator end() const;
    void insertFront(const E& e);
    void insertBack(const E& e);
    void insert(const Iterator& p, const E& e);
    void eraseFront();
    void eraseBack();
    void erase(const Iterator& p);

   private:
    int n;
    Node* header;
    Node* trailer;
};

template <typename E>
NodeList<E>::Iterator::Iterator(Node* u) {
    v = u;
}

template <typename E>
E& NodeList<E>::Iterator::operator*() {
    return v->elem;
}

template <typename E>
bool NodeList<E>::Iterator::operator==(const Iterator& p) const {
    return v == p.v;
}

template <typename E>
bool NodeList<E>::Iterator::operator!=(const Iterator& p) const {
    return v != p.v;
}

template <typename E>
typename NodeList<E>::Iterator& NodeList<E>::Iterator::operator++() {
    v = v->next;
    return *this;
}

template <typename E>
typename NodeList<E>::Iterator& NodeList<E>::Iterator::operator--() {
    v = v->prev;
    return *this;
}

template <typename E>
NodeList<E>::NodeList() {
    n = 0;
    header = new Node;
    trailer = new Node;
    header->next = trailer;
    trailer->prev = header;
}

template <typename E>
int NodeList<E>::size() const {
    return n;
}

template <typename E>
bool NodeList<E>::empty() const {
    return n == 0;
}

template <typename E>
typename NodeList<E>::Iterator NodeList<E>::begin() const {
    return Iterator(header->next);
}

template <typename E>
typename NodeList<E>::Iterator NodeList<E>::end() const {
    return Iterator(trailer);
}

// insert before
template <typename E>
void NodeList<E>::insert(const Iterator& p, const E& e) {
    auto node = p.v;
    auto newest = new Node;
    newest->elem = e;
    newest->next = node;
    newest->prev = node->prev;
    node->prev->next = newest;
    node->prev = newest;
    n++;
}

template<typename E>
void NodeList<E>::insertFront(const E &e) {
    insert(begin(), e);
}

template<typename E>
void NodeList<E>::insertBack(const E &e) {
    insert(end(), e);
}

template<typename E>
void NodeList<E>::erase(const Iterator &p) {
    auto node = p.v;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    n--;
}

template<typename E>
void NodeList<E>::eraseFront() {
    erase(begin());
}

template<typename E>
void NodeList<E>::eraseBack() {
    erase(--end());
}

}  // namespace tongfu
