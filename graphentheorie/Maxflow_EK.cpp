umap<int,umap<int, int>> a;
void init() { a.clear(); }
void addedge(int i, int j, int c) { a[i][j] += c; }
int ek(int S, int T) {
  int flow = 0;
  for(;;) {
    umap<int, int> p, m;
    queue<int> q;
    q.push(S);
    p[S] = S;
    m[S] = inf;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (auto& e: a[x]) {
        int y = e.first, c = e.second;
        if (!c || contains(p, y)) continue;
        p[y] = x;
        m[y] = min(m[x], c);
        q.push(y);
      }
    }
    if (!contains(p, T)) break;
    int delta = m[T];
    for (int x = T; p[x] != x; x = p[x]) {
      a[p[x]][x] -= delta;
      a[x][p[x]] += delta;
    }
    flow += delta;
  }
  return flow;
}
