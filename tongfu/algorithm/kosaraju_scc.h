#include <vector>

#include "tongfu/algorithm/depth_first_order.h"
#include "tongfu/algorithm/digraph.h"

namespace tongfu {

class KosarajuSCC {
   public:
    KosarajuSCC(Digraph& g) : marked_(g.V()), id_(g.V()), count_(0) {
        Digraph rg = g.reverse();
        DepthFirstOrder order(rg);
        for (int v : order.reversePost()) {
            if (!marked_[v]) {
                dfs(g, v);
                count_++;
            }
        }
    }

    int count() const { return count_; }

    bool stronglyConnected(int v, int w) const { return id_[v] == id_[w]; }

    int id(int v) const { return id_[v]; }

   private:
    void dfs(Digraph& g, int v) {
        marked_[v] = true;
        id_[v] = count_;
        for (int w : g.adj(v))
            if (!marked_[w]) dfs(g, w);
    }

   private:
    std::vector<bool> marked_;
    std::vector<int> id_;
    int count_;
};

}  // namespace tongfu
