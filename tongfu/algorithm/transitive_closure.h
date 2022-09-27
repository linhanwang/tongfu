#include <vector>
#include "tongfu/algorithm/directed_dfs.h"

namespace tongfu {

class TransitiveClosure {
public:
    TransitiveClosure(Digraph& g) {
        for (int v = 0; v < g.V(); ++v)
            tc.push_back(DirectedDfs(g, v));
    }

    bool reachable(int v, int w) const {
        return tc[v].marked(w);
    }
private:
    std::vector<DirectedDfs> tc;
};

}
