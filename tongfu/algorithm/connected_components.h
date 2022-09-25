#include <vector>
#include "tongfu/algorithm/graph.h"

namespace tongfu {

class CC {
public:
    CC(Graph& g) : marked_(g.V()), id_(g.V()), count_(0) {
        for (int s = 0; s < g.V(); ++s) {
            if (marked_[s]) continue;
            dfs(g, s);
            ++count_;
        }
    }

    bool connected(int v, int w) const {
        return id_[v] == id_[w];
    }

    int id(int v) const {
        return id_[v];
    }

    int count() const {
        return count_;
    }
private:
    void dfs(Graph& g, int v) {
        marked_[v] = true;
        id_[v] = count_;
        for (int w : g.adj(v)) {
            if (!marked_[w])
                dfs(g, w);
        }
    }
private:
    std::vector<bool> marked_;
    std::vector<int> id_;
    int count_;
};

}
