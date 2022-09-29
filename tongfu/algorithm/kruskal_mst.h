#include <functional>
#include <vector>
#include <queue>

#include "tongfu/algorithm/edge_weighted_graph.h"
#include "tongfu/container/UF.h"

namespace tongfu {

class KruskalMST {
public:
    KruskalMST(EdgeWeightedGraph& g) {
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq_;
        for (Edge e : g.edges())
            pq_.push(e);

        UF uf(g.V());
        while(!pq_.empty() && mst_.size() < g.V()-1) {
            Edge e = pq_.top();
            pq_.pop();
            int v = e.either();
            int w = e.other(v);
            if (uf.connected(v, w)) continue;
            uf.Union(v, w);
            weight_ += e.weight();
            mst_.push_back(e);
        }
    }

    const std::vector<Edge>& edges() const {
        return mst_;
    }

    double weight() const { return weight_; }
private:
    std::vector<Edge> mst_;
    double weight_;
};

}
