#include <algorithm>
#include <vector>

#include "tongfu/algorithm/digraph.h"

namespace tongfu {

class DepthFirstOrder {
   public:
    DepthFirstOrder(Digraph& g) : marked_(g.V()) {
        for (int v = 0; v < g.V(); ++v)
            if (!marked_[v]) dfs(g, v);

        reversePost_ = std::vector<int>(post_.rbegin(), post_.rend());
    }
    const std::vector<int>& pre() const { return pre_; }
    const std::vector<int>& post() const { return post_; }
    const std::vector<int>& reversePost() const { return reversePost_; }

   private:
    void dfs(Digraph& g, int v) {
        pre_.push_back(v);

        marked_[v] = true;
        for (int w : g.adj(v))
            if (!marked_[w]) dfs(g, w);

        post_.push_back(v);
    }

   private:
    std::vector<int> marked_;
    std::vector<int> pre_;
    std::vector<int> post_;
    std::vector<int> reversePost_;
};

}  // namespace tongfu
