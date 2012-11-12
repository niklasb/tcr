#include <algorithm>

// edge_t fehlt, root und join ist das uebliche union-find
int kruskal() {
    vector<int> parent(nr_of_nodes, -1);
    int rem = nr_of_nodes - 1, ans = 0;

    sort(edges.begin(), edges.end());
    for (vector<edge_t>::iterator it = edges.begin(); rem > 0 && it != edges.end(); ++it) {
        int a = root(parent, it->from), b = root(parent, it->to);
        if (a != b) {
            join(parent, a, b);
            ans += it->len;
            --rem;
        }
    }
    return ans;
}
