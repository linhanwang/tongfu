#include <iostream>
#include <istream>
#include <vector>
#include "tongfu/algorithm/edge.h"

namespace tongfu {

class EdgeWeightedGraph {
public:
    EdgeWeightedGraph(int V) : V_(V), E_(0), adj_(V_) {}


    int V() const { return V_; }
    int E() const { return E_; }

    void addEdge(Edge e) {
        int v = e.either();
        int w = e.other(v);
        adj_[v].push_back(e);
        adj_[w].push_back(e);
        E_++;
    }

    const std::vector<Edge>& adj(int v) const {
        return adj_[v];
    }

    int degree(int v) const {
        return adj_[v].size();
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> res;
        for (int v = 0; v < V_; ++v)
            for (Edge e : adj(v))
                if (e.other(v) > v) res.push_back(e);
        return res;
    }
private:
    int V_;
    int E_;
    std::vector<std::vector<Edge>> adj_;
};
    
inline EdgeWeightedGraph buildEdgeWeightedGraphFromStdin(std::istream& in) {
        int V, E;
        in >> V;
        in >> E;
        EdgeWeightedGraph g(V);
        for (int i = 0; i < E; ++i) {
            int v, w;
            double weight;
            in >> v >> w >> weight;
            g.addEdge(Edge(v, w, weight));
        }

        return g;
    }

}
