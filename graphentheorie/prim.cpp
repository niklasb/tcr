// alles wie bei Dijkstra
int prim(vvii& gr) {
    vector<int> dist(gr.size(), INF);
    priority_queue<ii, vii, greater<ii> > kew;
    int ans = 0;

    dist[0] = 0;
    for (kew.push(ii(0, 0)); !kew.empty(); kew.pop()) {
        int d = kew.top().first, fr = kew.top().second;
        if (d <= dist[fr]) {
            ans += d;
            dist[fr] = -1;
            for (vii::iterator it = gr[fr].begin(); it != gr[fr].end(); ++it) {
                int to = it->first, len = it->second;
                if (dist[to] > len) kew.push(ii(dist[to] = len, to));
            }
        }
    }
    return ans;
}
