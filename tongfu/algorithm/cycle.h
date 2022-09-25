#pragma once

#include <vector>

#include "tongfu/algorithm/graph.h"

namespace tongfu {

class Cycle {
   public:
    Cycle(Graph& g) : marked_(g.V()), hasCycle_(false) {
        for (int s = 0; s < g.V(); ++s) {
            if (!marked_[s]) dfs(g, s, s);
        }
    }

    bool hasCycle() const { return hasCycle_; }

   private:
    void dfs(Graph& g, int v, int u) {
        marked_[v] = true;
        for (int w : g.adj(v)) {
            if (!marked_[w]) {
                dfs(g, w, v);
            } else if (w != u) {
                hasCycle_ = true;
            }
        }
    }

   private:
    std::vector<bool> marked_;
    bool hasCycle_;
};

}  // namespace tongfu
