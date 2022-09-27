#include <vector>

#include "tongfu/algorithm/depth_first_order.h"
#include "tongfu/algorithm/digraph.h"
#include "tongfu/algorithm/directed_cycle.h"

namespace tongfu {

class Topological {
   public:
    Topological(Digraph& g) {
        DirectedCycle cyclefinder(g);
        if (!cyclefinder.hasCycle()) {
            DepthFirstOrder order(g);
            // we can guarantee that dfs(w) will return before than dfs(v) (v->w)
            // but we can't guarantee dfs(v) will be called before dfs(w)
            // As a result, reversePost (not pre) is in topological order.
            auto& temp = order.reversePost();
            order_.insert(order_.begin(), temp.begin(), temp.end());
        }
    }

    const std::vector<int>& order() const { return order_; }

    bool isDAG() const { return !order_.empty(); }
   private:
    std::vector<int> order_;
};

}  // namespace tongfu
