#include <functional>
#include <iostream>
#include <limits>
#include <vector>

#include "tongfu/algorithm/edge_weighted_digraph.h"

namespace tongfu {

class AcyclicSP {
    static constexpr double DMax = std::numeric_limits<double>::max();

   public:
    AcyclicSP(EdgeWeightedDigraph& g, int s)
        : edgeTo_(g.V(), DirectedEdge(-1, -1, DMax)),
          distTo_(g.V(), DMax),
          marked_(g.V(), false) {
        distTo_[s] = 0.0;
        topological(g);
        for (int v : order_) relax(g, v);
    }

    double distTo(int v) const { return distTo_[v]; }

    bool hasPathTo(int v) const { return distTo_[v] < DMax; }

    std::vector<DirectedEdge> pathTo(int v) const {
        if (!hasPathTo(v)) return {};
        std::vector<DirectedEdge> path;
        for (DirectedEdge e = edgeTo_[v]; e.weight() != DMax;
             e = edgeTo_[e.from()])
            path.push_back(e);
        std::reverse(path.begin(), path.end());
        return path;
    }

   private:
    void relax(EdgeWeightedDigraph& g, int v) {
        for (DirectedEdge e : g.adj(v)) {
            int w = e.to();
            if (distTo_[w] > distTo_[v] + e.weight()) {
                distTo_[w] = distTo_[v] + e.weight();
                edgeTo_[w] = e;
            }
        }
    }

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
    std::vector<DirectedEdge> edgeTo_;
    std::vector<double> distTo_;
    std::vector<int> order_;
    std::vector<bool> marked_;
};

}  // namespace tongfu
