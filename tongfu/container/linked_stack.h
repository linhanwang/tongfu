#include <cassert>

#include "tongfu/container/singly_linked_list.h"

namespace tongfu {

template <typename E>
class LinkedStack {
   public:
    LinkedStack();
    int size() const;
    bool empty() const;
    const E& top() const;
    void push(const E& e);
    void pop();

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const LinkedStack<Entry>&);

   private:
    SLinkedList<E> S;
    int n;
};

template <typename E>
LinkedStack<E>::LinkedStack() : S(), n(0) {}

template <typename E>
int LinkedStack<E>::size() const {
    return n;
}

template <typename E>
bool LinkedStack<E>::empty() const {
    return n == 0;
}

template <typename E>
const E& LinkedStack<E>::top() const {
    assert(!empty());
    return S.front();
}

template <typename E>
void LinkedStack<E>::push(const E& e) {
    ++n;
    S.addFront(e);
}

template <typename E>
void LinkedStack<E>::pop() {
    assert(!empty());

    --n;
    S.removeFront();
}

template <typename Entry>
inline std::ostream& operator<<(std::ostream& out,
                                const LinkedStack<Entry>& s) {
    out << s.S;
    return out;
}

}  // namespace tongfu
