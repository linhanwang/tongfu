#include <functional>
#include <queue>
#include <vector>

#include "tongfu/algorithm/edge_weighted_graph.h"

namespace tongfu {

class LazyPrimeMST {
   public:
    LazyPrimeMST(EdgeWeightedGraph& g) : marked_(g.V()) {
        visit(g, 0);  // we assume g is connected
        while (!pq_.empty()) {
            Edge e = pq_.top();
            pq_.pop();

            int v = e.either();
            int w = e.other(v);
            if (marked_[v] && marked_[w])
                continue;  // lazy, both v and w already visited
            mst_.push_back(e);
            weight_ += e.weight();
            if (!marked_[v]) visit(g, v);
            if (!marked_[w]) visit(g, w);
        }
    }

    double weight() const { return weight_; }

    const std::vector<Edge>& edges() const { return mst_; }

   private:
    /*
     * add all edges e incident to v onto pq_ if the other endpoint has not yet
     * be visited
     * */
    void visit(EdgeWeightedGraph& g, int v) {
        marked_[v] = true;
        for (Edge e : g.adj(v))
            if (!marked_[e.other(v)]) pq_.push(e);
    }

   private:
    double weight_;
    std::vector<bool> marked_;
    std::vector<Edge> mst_;
    std::priority_queue<Edge, std::vector<Edge>, std::greater<>> pq_;
};

}  // namespace tongfu
