#pragma once

#include <vector>

#include "tongfu/algorithm/digraph.h"

namespace tongfu {

class DirectedDfs {
   public:
    DirectedDfs(Digraph& g, int s) : marked_(g.V(), false), count_(0) {
        dfs(g, s);
    }

    int count() const { return count_; }

    bool marked(int v) const { return marked_[v]; }

   private:
    void dfs(Digraph& g, int v) {
        marked_[v] = true;
        count_++;
        for (int w : g.adj(v))
            if (!marked_[w]) dfs(g, w);
    }

   private:
    std::vector<bool> marked_;
    int count_;
};

}  // namespace tongfu
