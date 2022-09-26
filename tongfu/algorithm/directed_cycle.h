#include <iostream>
#include <vector>

#include "tongfu/algorithm/digraph.h"

namespace tongfu {

class DirectedCycle {
   public:
    DirectedCycle(Digraph& g)
        : onStack_(g.V()), edgeTo_(g.V()), marked_(g.V()) {
        for (int v = 0; v < g.V(); ++v)
            if (!marked_[v]) dfs(g, v);
    }

    bool hasCycle() const { return !cycle_.empty(); }

    std::vector<int> cycle() const { return cycle_; }

   private:
    void dfs(Digraph& g, int v) {
        std::cout << v << std::endl;
        onStack_[v] = true;
        marked_[v] = true;
        for (int w : g.adj(v)) {
            if (hasCycle())
                return;
            else if (!marked_[w]) {
                edgeTo_[w] = v;
                dfs(g, w);
            } else if (onStack_[w]) {
                for (int x = v; x != w; x = edgeTo_[x]) {
                    cycle_.push_back(x);
                }
                cycle_.push_back(w);
                cycle_.push_back(v);
            }
        }
        onStack_[v] = false;
    }

   private:
    std::vector<bool> marked_;
    std::vector<int> edgeTo_;
    std::vector<int> cycle_;
    std::vector<bool> onStack_;
};

}  // namespace tongfu
