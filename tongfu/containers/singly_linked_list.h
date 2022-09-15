#pragma once

#include <ostream>

namespace tongfu {
namespace containers {

template <typename E>
class SLinkedList;

template <typename E>
class SNode {
   public:
    friend class SLinkedList<E>;

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const SLinkedList<Entry>&);

   private:
    SNode(const E& e, SNode<E>* n) {
        elem = e;
        next = n;
    }

    E elem;
    SNode<E>* next;
};

template <typename E>
class SLinkedList {
   public:
    SLinkedList();
    ~SLinkedList();
    bool empty() const;
    const E& front() const;
    void addFront(const E& e);
    void removeFront();

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const SLinkedList<Entry>&);

   private:
    SNode<E>* head;
};

template <typename E>
SLinkedList<E>::SLinkedList() : head(nullptr) {}

template <typename E>
bool SLinkedList<E>::empty() const {
    return head == nullptr;
}

template <typename E>
const E& SLinkedList<E>::front() const {
    return head->elem;
}

template <typename E>
SLinkedList<E>::~SLinkedList() {
    while (!empty()) removeFront();
}

template <typename E>
void SLinkedList<E>::addFront(const E& e) {
    SNode<E>* v = new SNode<E>(e, head);
    head = v;
}

template <typename E>
void SLinkedList<E>::removeFront() {
    SNode<E>* old = head;
    head = old->next;
    delete old;
}

template <typename E>
std::ostream& operator<<(std::ostream& out, const SLinkedList<E>& l) {
    out << "[";
    SNode<E>* cursor = l.head;
    while (cursor != nullptr) {
        out << cursor->elem << ",";
        cursor = cursor->next;
    }
    out << "]";
    return out;
}

}  // namespace containers
}  // namespace tongfu
