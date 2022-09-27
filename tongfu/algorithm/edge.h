#include <ostream>

namespace tongfu {

class Edge {
   public:
    Edge(int v, int w, double weight) : v_(v), w_(w), weight_(weight) {}

    double weight() const { return weight_; }

    int either() const { return v_; }
    int other(int v) const { return (v == v_) ? w_ : v_; }
    bool operator<(const Edge& e) const { return weight_ < e.weight(); }
    bool operator>(const Edge& e) const { return weight_ > e.weight(); }

    friend std::ostream& operator<<(std::ostream& out, const Edge& e);

   private:
    int v_;
    int w_;
    double weight_;
};

inline std::ostream& operator<<(std::ostream& out, const Edge& e) {
    out << "(v=" << e.v_ << ",w=" << e.w_ << ",weight=" << e.weight_ << ")";
    return out;
}

}  // namespace tongfu
