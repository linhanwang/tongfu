#pragma once

#include <ostream>

namespace tongfu {

template <typename K, typename V>
class Entry {
   public:
    Entry(const K& k = K(), const V& v = V()) : _key(k), _value(v) {}
    const K& key() const { return _key; }
    const V& value() const { return _value; }
    void setKey(const K& k) { _key = k; }
    void setValue(const V& v) { _value = v; }

    template <typename X, typename Y>
    friend std::ostream& operator<<(std::ostream&, const Entry<X, Y>& e);

   private:
    K _key;
    V _value;
};

template <typename K, typename V>
inline std::ostream& operator<<(std::ostream& out, const Entry<K, V>& e) {
    out << e.key();
    return out;
}

}  // namespace tongfu
