#include <vector>
#include <queue>
#include <functional>
#include <utility>

const int INF = 12345678;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

// Anzahl der Knoten = gr.size()
// Grad des Knotens i = gr[i].size()
// j-ter benachbarter Knoten des Knotens i = gr[i][j].first
// Laenge dieser Kante = gr[i][j].second
vector<int> dijkstra(vvii& gr, int src) {
    vector<int> dist(gr.size(), INF);
    priority_queue<ii, vii, greater<ii> > kew;

    dist[src] = 0;
    for (kew.push(ii(0, src)); !kew.empty(); kew.pop()) {
        int d = kew.top().first, fr = kew.top().second;
        if (d <= dist[fr]) {
            for (vii::iterator it = gr[fr].begin(); it != gr[fr].end(); ++it) {
                int to = it->first, len = it->second;
                if (dist[to] > d + len) kew.push(ii(dist[to] = d + len, to));
            }
        }
    }

    return dist;
}
