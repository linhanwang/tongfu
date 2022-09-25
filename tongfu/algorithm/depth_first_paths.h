#pragma once

#include <algorithm>
#include <vector>

#include "tongfu/algorithm/graph.h"

namespace tongfu {

class DepthFirstPaths {
   public:
    DepthFirstPaths(Graph& g, int s) : s_(s), marked_(g.V()), edgeTo_(g.V()) {
        dfs(g, s_);
    }

    bool hasPthTo(int v) const { return marked_[v]; }

    std::vector<int> pathTo(int v) {
        if (!hasPthTo(v)) return {};
        std::vector<int> path;
        for (int x = v; x != s_; x = edgeTo_[x]) path.push_back(x);
        path.push_back(s_);
        std::reverse(path.begin(), path.end());
        return path;
    }

   private:
    void dfs(Graph& g, int v) {
        marked_[v] = true;
        for (int w : g.adj(v)) {
            if (!marked_[w]) {
                edgeTo_[w] = v;
                dfs(g, w);
            }
        }
    }

   private:
    std::vector<bool> marked_;
    std::vector<int> edgeTo_;
    int s_;
};

}  // namespace tongfu
