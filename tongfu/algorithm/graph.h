#include <vector>

namespace tongfu {

class Graph {
   public:
    Graph(int v) : V_(v), adj_(v) {}

    int V() const { return V_; }

    int E() const { return E_; }

    void addEdge(int v, int w) {
        adj_[v].push_back(w);
        adj_[w].push_back(v);
        ++E_;
    }

    const std::vector<int>& adj(int v) const { return adj_[v]; }

   private:
    int V_;
    int E_;
    std::vector<std::vector<int>> adj_;
};

}  // namespace tongfu
