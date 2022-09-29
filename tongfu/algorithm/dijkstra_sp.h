#include <functional>
#include <limits>
#include <vector>

#include "tongfu/algorithm/edge_weighted_digraph.h"
#include "tongfu/container/index_priority_queue.h"

namespace tongfu {

class DijkstraSP {
    static constexpr double DMax = std::numeric_limits<double>::max();

   public:
    DijkstraSP(EdgeWeightedDigraph& g, int s)
        : edgeTo_(g.V(), DirectedEdge(-1, -1, DMax)),
          pq_(g.V()),
          distTo_(g.V(), DMax) {
        distTo_[s] = 0.0;
        pq_.insert(s, 0.0);
        while (!pq_.isEmpty()) {
            int v = pq_.topIndex();
            pq_.pop();
            relax(g, v);
        }
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
                if (pq_.contains(w))
                    pq_.changeKey(w, distTo_[w]);
                else
                    pq_.insert(w, distTo_[w]);
            }
        }
    }

   private:
    std::vector<DirectedEdge> edgeTo_;
    std::vector<double> distTo_;
    IndexPQ<double, std::greater<double>> pq_;
};

}  // namespace tongfu
