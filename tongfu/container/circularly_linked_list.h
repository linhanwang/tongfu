#pragma once

#include <ostream>

namespace tongfu {

template <typename E>
class CircleList;

template <typename E>
class CNode {
   private:
    E elem;
    CNode* next;

    friend class CircleList<E>;

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const CircleList<Entry>&);
};

template <typename E>
class CircleList {
   public:
    CircleList();
    ~CircleList();
    bool empty() const;
    const E& front() const;
    const E& back() const;
    void advance();
    void addFront(const E& e);
    void removeFront();

    template <typename Entry>
    friend std::ostream& operator<<(std::ostream&, const CircleList<Entry>&);

   private:
    CNode<E>* cursor;
};

template <typename E>
CircleList<E>::CircleList() : cursor(nullptr) {}

template <typename E>
CircleList<E>::~CircleList() {
    while (!empty()) {
        removeFront();
    }
}

template <typename E>
bool CircleList<E>::empty() const {
    return cursor == nullptr;
}

template <typename E>
const E& CircleList<E>::front() const {
    return cursor->next->elem;
}

template <typename E>
const E& CircleList<E>::back() const {
    return cursor->elem;
}

template <typename E>
void CircleList<E>::advance() {
    cursor = cursor->next;
}

template<typename E>
void CircleList<E>::addFront(const E& e) {
    CNode<E>* v = new CNode<E>();
    v->elem = e;
    if (cursor == nullptr) {
        v->next = v;
        cursor = v;
    } else {
        v->next = cursor->next;
        cursor->next = v;
    }
}

template <typename E>
void CircleList<E>::removeFront() {
    CNode<E>* old = cursor->next;
    if (old == cursor) {
        cursor = nullptr;
    } else {
        cursor->next = old->next;
    }
    delete old;
}

template <typename E>
inline std::ostream& operator<<(std::ostream& out, const CircleList<E>& l) {
    if (l.empty()) {
        out << "[]";
        return out;
    }
    out << "[";
    auto cur = l.cursor->next;
    while (cur != l.cursor) {
        out << cur->elem << ",";
        cur = cur->next;
    }
    out << l.cursor->elem << "]";
    return out;
}

}  // namespace tongfu
