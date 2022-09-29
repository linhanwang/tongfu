#include <functional>
#include <limits>
#include <vector>

#include "tongfu/algorithm/edge_weighted_graph.h"
#include "tongfu/container/index_priority_queue.h"

namespace tongfu {

class PrimeMST {
   public:
    PrimeMST(EdgeWeightedGraph& g)
        : edgeTo_(g.V(), Edge(-1, -1, -1.0)),
          distTo_(g.V(), std::numeric_limits<double>::max()),
          marked_(g.V()),
          pq_(g.V()) {
        distTo_[0] = 0;
        pq_.insert(0, 0.0);
        while (!pq_.isEmpty()) {
            int v = pq_.topIndex();
            pq_.pop();
            visit(g, v);
        }
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> mst;
        for (int v = 0; v < edgeTo_.size(); ++v) {
            Edge e = edgeTo_[v];
            if (e.weight() >= 0.0) {
                mst.push_back(e);
            }
        }
        return mst;
    }

    double weight() const {
        double weight = 0;
        for (Edge e : edges()) weight += e.weight();
        return weight;
    }

   private:
    void visit(EdgeWeightedGraph& g, int v) {
        marked_[v] = true;
        for (Edge e : g.adj(v)) {
            int w = e.other(v);
            if (marked_[w]) continue;
            if (e.weight() < distTo_[w]) {
                edgeTo_[w] = e;
                distTo_[w] = e.weight();
                if (pq_.contains(w))
                    pq_.changeKey(w, distTo_[w]);
                else
                    pq_.insert(w, distTo_[w]);
            }
        }
    }

   private:
    double weight_;
    std::vector<Edge> edgeTo_;
    std::vector<double> distTo_;
    std::vector<bool> marked_;
    IndexPQ<double, std::greater<double>> pq_;
};

}  // namespace tongfu
