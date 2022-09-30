#include <queue>

#include "tongfu/algorithm/sp.h"
#include "tongfu/container/index_priority_queue.h"

namespace tongfu {

class DijkstraSP : public SP {
   public:
    DijkstraSP(EdgeWeightedDigraph& g, int s) : SP(g, s), pq_(g.V()) {
        pq_.insert(s, 0.0);
        while (!pq_.isEmpty()) {
            int v = pq_.topIndex();
            pq_.pop();
            relax(g, v);
        }
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
    IndexPQ<double, std::greater<double>> pq_;
};

class DijkstraSPSimple : public SP {
    using Pair = std::pair<double, int>;

   public:
    DijkstraSPSimple(EdgeWeightedDigraph& g, int s) : SP(g, s) {
        distTo_[s] = 0.0;
        pq_.push({0.0, s});
        while (!pq_.empty()) {
            int v = pq_.top().second;
            pq_.pop();
            relax(g, v);
        }
    }

   private:
    void relax(EdgeWeightedDigraph& g, int v) {
        for (DirectedEdge e : g.adj(v)) {
            int w = e.to();
            if (distTo_[w] > distTo_[v] + e.weight()) {
                distTo_[w] = distTo_[v] + e.weight();
                edgeTo_[w] = e;
                pq_.push({e.weight(), w});  // add redundant instead of change
            }
        }
    }

   private:
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq_;
};

}  // namespace tongfu
