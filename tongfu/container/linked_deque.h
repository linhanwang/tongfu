#pragma once

#include <cassert>

#include "tongfu/container/doubly_linked_list.h"

namespace tongfu {

template <typename E>
class LinkedDeque {
   public:
    LinkedDeque();
    int size() const;
    bool empty() const;
    const E& front() const;
    const E& back() const;
    void insertFront(const E& e);
    void insertBack(const E& e);
    void removeFront();
    void removeBack();

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const LinkedDeque<Entry>&);

   private:
    DLinkedList<E> D;
    int n;
};

template <typename E>
LinkedDeque<E>::LinkedDeque() : D(), n(0) {}

template <typename E>
int LinkedDeque<E>::size() const {
    return n;
}

template <typename E>
bool LinkedDeque<E>::empty() const {
    return n == 0;
}

template <typename E>
const E& LinkedDeque<E>::front() const {
    return D.front();
}

template <typename E>
const E& LinkedDeque<E>::back() const {
    return D.back();
}

template <typename E>
void LinkedDeque<E>::insertFront(const E& e) {
    D.addFront(e);
    n++;
}

template <typename E>
void LinkedDeque<E>::insertBack(const E& e) {
    D.addBack(e);
    n++;
}

template <typename E>
void LinkedDeque<E>::removeFront() {
    assert(!empty());

    D.removeFront();
    n--;
}

template <typename E>
void LinkedDeque<E>::removeBack() {
    assert(!empty());

    D.removeBack();
    n--;
}

template <typename E>
inline std::ostream& operator<<(std::ostream& out, const LinkedDeque<E>& q) {
    out << q.D;
    return out;
}

}  // namespace tongfu
