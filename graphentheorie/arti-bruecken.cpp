#include <vector>

using namespace std;

const int MAX = 1024;

vector<vector<int> > graph;
int low[MAX], depth[MAX];
bool is_arti[MAX], is_bridge[MAX][MAX];

int visit(int nod, int par, int dep) {
    int children = 0;

    low[nod] = depth[nod] = dep;
    for (size_t i = 0; i < graph[nod].size(); ++i) {
        int k = graph[nod][i];

        if (depth[k] < 0) {
            ++children;
            visit(k, nod, dep + 1);
            if (low[nod] > low[k]) low[nod] = low[k];
            is_arti[nod] = is_arti[nod] || low[k] >= dep;
            is_bridge[nod][i] = low[k] > dep;
        } else if (k != par) {
            if (low[nod] > depth[k]) low[nod] = depth[k];
            is_bridge[nod][i] = false;
        }
    }
    return children;
}

void tarjan() {
    fill(depth, depth + graph.size(), -1);
    fill(is_arti, is_arti + graph.size(), false);
    for (size_t i = 0; i < graph.size(); ++i)
        fill(is_bridge[i], is_bridge[i] + graph[i].size(), true);
    for (size_t i = 0; i < graph.size(); ++i)
        if (depth[i] < 0) is_arti[i] = visit(i, i, 0) > 1;
}
