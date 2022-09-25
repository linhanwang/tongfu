#pragma once

#include <cassert>

#include "tongfu/container/circularly_linked_list.h"

namespace tongfu {

template <typename E>
class LinkedQueue {
   public:
    LinkedQueue();
    int size() const;
    bool empty() const;
    const E& front() const;
    void enqueue(const E& e);
    void dequeue();

    template<typename Entry>
    friend std::ostream& operator<<(std::ostream&, const LinkedQueue<Entry>&);

   private:
    CircleList<E> C;
    int n;
};

template<typename E>
LinkedQueue<E>::LinkedQueue() : C(), n(0) {}

template<typename E>
int LinkedQueue<E>::size() const { return n; }

template<typename E>
bool LinkedQueue<E>::empty() const { return n == 0; }

template<typename E>
const E& LinkedQueue<E>::front() const {
    assert(!empty());

    return C.front();
}

template<typename E>
void LinkedQueue<E>::enqueue(const E &e) {
    C.addFront(e);
    C.advance(); // move e to back o queue
    n++;
}

template<typename E>
void LinkedQueue<E>::dequeue() {
    assert(!empty());

    C.removeFront();
    n--;
}

template<typename E>
inline std::ostream& operator<<(std::ostream& out, const LinkedQueue<E>& q) {
    out << q.C;
    return out;
}

}  // namespace tongfu
