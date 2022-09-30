#include <functional>
#include <limits>
#include <vector>

#include "tongfu/algorithm/edge_weighted_digraph.h"

namespace tongfu {

class SP {
   protected:
    static constexpr double DMax = std::numeric_limits<double>::max();

   public:
    SP(EdgeWeightedDigraph& g, int s)
        : edgeTo_(g.V(), DirectedEdge(-1, -1, DMax)), distTo_(g.V(), DMax) {
        distTo_[s] = 0.0;
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

   protected:
    void relax(EdgeWeightedDigraph& g, int v) {
        for (DirectedEdge e : g.adj(v)) {
            int w = e.to();
            if (distTo_[w] > distTo_[v] + e.weight()) {
                distTo_[w] = distTo_[v] + e.weight();
                edgeTo_[w] = e;
            }
        }
    }

   protected:
    std::vector<DirectedEdge> edgeTo_;
    std::vector<double> distTo_;
};

}  // namespace tongfu
