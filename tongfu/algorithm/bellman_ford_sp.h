#include <queue>
#include <vector>
#include "tongfu/algorithm/sp.h"

namespace tongfu {

class BellmanFordSP : public SP {
   public:
    BellmanFordSP(EdgeWeightedDigraph& g, int s) : SP(g, s), onQ_(g.V()) {
        q_.push(s);
        onQ_[s] = true;
        while (!q_.empty()) {
            int v = q_.front();
            q_.pop();
            onQ_[v] = false;
            relax(g, v);
        }
    }

   private:
    void relax(EdgeWeightedDigraph& g, int v) {
        for (DirectedEdge e : g.adj(v)) {
            relax(e);
        }
    }

    void relax(DirectedEdge e) {
        int v = e.from();
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight()) {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
            if (!onQ_[w]) {
                q_.push(w);
                onQ_[w] = true;
            }
        }
    }

private:
    std::queue<int> q_;
    std::vector<bool> onQ_;
};

class BellmanFordSimpleSP : public SP {
   public:
    BellmanFordSimpleSP(EdgeWeightedDigraph& g, int s) : SP(g, s) {
        for (int v = 0; v < g.V(); ++v)
            for (DirectedEdge e : g.edges()) relax(e);
    }

   private:
    void relax(DirectedEdge e) {
        int v = e.from();
        int w = e.to();
        if (distTo_[w] > distTo_[v] + e.weight()) {
            distTo_[w] = distTo_[v] + e.weight();
            edgeTo_[w] = e;
        }
    }
};

}  // namespace tongfu
