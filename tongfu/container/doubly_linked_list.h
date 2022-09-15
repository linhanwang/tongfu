#pragma once

#include <iostream>
#include <ostream>

namespace tongfu {
namespace container {

template <typename E>
class DLinkedList;

template <typename E>
class DNode {
   public:
    friend class DLinkedList<E>;

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const DLinkedList<Entry>&);

   private:
    DNode(const E& e, DNode<E>* p, DNode<E>* n) {
        elem = e;
        prev = p;
        next = n;
    }

    E elem;
    DNode<E>* prev;
    DNode<E>* next;
};

template <typename E>
class DLinkedList {
   public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    const E& front() const;
    const E& back() const;
    void addFront(const E& e);
    void addBack(const E& e);
    void removeFront();
    void removeBack();

    template<typename Entry>
    friend std::ostream& operator<<(std::ostream&, const DLinkedList<Entry>&);

   protected:
    void addBefore(DNode<E>* v, const E& e);
    void remove(DNode<E>* v);

   private:
    DNode<E>* header;
    DNode<E>* trailer;
};

template <typename E>
DLinkedList<E>::DLinkedList() {
    header = new DNode<E>(E(), nullptr, nullptr);
    trailer = new DNode<E>(E(), nullptr, nullptr);
    header->next = trailer;
    trailer->prev = header;
}

template <typename E>
DLinkedList<E>::~DLinkedList() {
    while (!empty()) {
        removeFront();
    }
    delete header;
    delete trailer;
}

template <typename E>
bool DLinkedList<E>::empty() const {
    return header->next == trailer;
}

template <typename E>
const E& DLinkedList<E>::front() const {
    return header->next->elem;
}

template <typename E>
const E& DLinkedList<E>::back() const {
    return trailer->prev->elem;
}

template <typename E>
void DLinkedList<E>::addBefore(DNode<E>* v, const E& e) {
    DNode<E>* newest = new DNode<E>(e, v->prev, v);
    v->prev->next = newest;
    v->prev = newest;
}

template <typename E>
void DLinkedList<E>::addFront(const E& e) {
    addBefore(header->next, e);
}

template <typename E>
void DLinkedList<E>::addBack(const E& e) {
    addBefore(trailer, e);
}

template <typename E>
void DLinkedList<E>::remove(DNode<E>* v) {
    v->prev->next = v->next;
    v->next->prev = v->prev;
    delete v;
}

template <typename E>
void DLinkedList<E>::removeFront() {
    remove(header->next);
}

template <typename E>
void DLinkedList<E>::removeBack() {
    remove(trailer->prev);
}

template <typename E>
inline std::ostream& operator<<(std::ostream& out, const DLinkedList<E>& l) {
    out << "[";
    DNode<E>* cursor = l.header->next;
    while (cursor != l.trailer) {
        out << cursor->elem << ",";
        cursor = cursor->next;
    }
    out << "]";
    return out;
}

}  // namespace container
}  // namespace tongfu
