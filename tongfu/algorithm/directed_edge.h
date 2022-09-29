#include <iostream>

namespace tongfu {

class DirectedEdge {
   public:
    DirectedEdge(int v, int w, double weight) : v_(v), w_(w), weight_(weight) {}

    double weight() const { return weight_; }

    int from() const { return v_; }

    int to() const { return w_; }

    bool operator<(const DirectedEdge& e) const { return weight_ < e.weight(); }

    bool operator>(const DirectedEdge& e) const { return weight_ > e.weight(); }

    friend std::ostream& operator<<(std::ostream& out, const DirectedEdge& e);

   private:
    int v_;
    int w_;
    double weight_;
};

inline std::ostream& operator<<(std::ostream& out, const DirectedEdge& e) {
    out << "(v=" << e.v_ << ",w=" << e.w_ << ",weight=" << e.weight_ << ")";
    return out;
}

}  // namespace tongfu
