#pragma once

#include <vector>
#include <iostream>

namespace tongfu {

class Digraph {
   public:
    Digraph(int v) : V_(v), adj_(v) {}

    int V() const { return V_; }

    int E() const { return E_; }

    /*
     * directed edge v -> w
     * */
    void addEdge(int v, int w) {
        adj_[v].push_back(w);
        ++E_;
    }

    /*
     * add v->w and w->v two edges
     * */
    void addBiEdge(int v, int w) {
        addEdge(v, w);
        addEdge(w, v);
    }

    const std::vector<int>& adj(int v) const { return adj_[v]; }

    Digraph reverse() const {
        Digraph R(V_);
        for (int v = 0; v < V_; ++v)
            for (int w : adj_[v])
                R.addEdge(w, v);

        return R;
    }

   private:
    int V_;
    int E_;
    std::vector<std::vector<int>> adj_;
};

inline Digraph buildDigraphFromStdin() {
    int v, e;
    std::cin >> v >> e;
    Digraph g(v);
    for (int i = 0; i < e; ++i) {
        int s, d;
        std::cin >> s >> d;
        g.addEdge(s, d);
    }
    return g;
}

}  // namespace tongfu
