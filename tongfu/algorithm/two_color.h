#pragma once

#include <vector>

#include "tongfu/algorithm/graph.h"

namespace tongfu {

class TwoColor {
   public:
    TwoColor(Graph& g) : marked_(g.V()), color_(g.V()) {
        for (int s = 0; s < g.V(); ++s)
            if (!marked_[s]) dfs(g, s);
    }

    bool isBipartite() const { return isTwoColorable; }

   private:
    void dfs(Graph& g, int v) {
        marked_[v] = true;
        for (int w : g.adj(v)) {
            if (!marked_[w]) {
                color_[w] = !color_[v];
                dfs(g, w);
            } else if (color_[w] == color_[v])
                isTwoColorable = false;
        }
    }

   private:
    std::vector<bool> marked_;
    std::vector<bool> color_;
    bool isTwoColorable = true;
};

}  // namespace tongfu
