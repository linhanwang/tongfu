#include <iostream>

#include "tongfu/algorithm/sp.h"

namespace tongfu {

class AcyclicSP : public SP {
   public:
    AcyclicSP(EdgeWeightedDigraph& g, int s) : SP(g, s), marked_(g.V(), false) {
        topological(g);
        for (int v : order_) relax(g, v);
    }

   private:
    void topological(EdgeWeightedDigraph& g) {
        for (int v = 0; v < g.V(); ++v)
            if (!marked_[v]) dfs(g, v);
        std::reverse(order_.begin(), order_.end());
    }

    void dfs(EdgeWeightedDigraph& g, int v) {
        marked_[v] = true;
        for (DirectedEdge e : g.adj(v)) {
            int w = e.to();
            if (!marked_[w]) dfs(g, w);
        }
        order_.push_back(v);
    }

   private:
    std::vector<int> order_;
    std::vector<bool> marked_;
};

}  // namespace tongfu
