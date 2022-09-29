#include <vector>
#include "tongfu/algorithm/directed_edge.h"

namespace tongfu {

class EdgeWeightedDigraph {
   public:
    EdgeWeightedDigraph(int V) : V_(V), E_(0), adj_(V_) {}

    int V() const { return V_; }

    int E() const { return E_; }

    const std::vector<DirectedEdge>& adj(int v) const {
        return adj_[v];
    }

    void addEdge(DirectedEdge e) {
        adj_[e.from()].push_back(e);
        E_++;
    }

    std::vector<DirectedEdge> edges() const {
        std::vector<DirectedEdge> res;
        for (int v = 0; v < V_; ++v)
            for (DirectedEdge e : adj_[v])
                res.push_back(e);
        return res;
    }
private:
    int V_;
    int E_;
    std::vector<std::vector<DirectedEdge>> adj_;
};

inline EdgeWeightedDigraph buildEdgeWeightedDigraphFromStdin(std::istream& in) {
    int V, E;
    in >> V;
    in >> E;
    EdgeWeightedDigraph g(V);
    for (int i = 0; i < E; ++i) {
        int v, w;
        double weight;
        in >> v >> w >> weight;
        g.addEdge(DirectedEdge(v, w, weight));
    }

    return g;
}
}
