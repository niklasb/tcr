// FF with cap scaling, O(m^2 log C)
const int MAXN = 190000, MAXC = 1<<29;
struct edge { int dest,capacity,reversed_index; };
vector<edge> adj[MAXN];
int vis[MAXN], target, iter, cap;

void addedge(int x,int y,int c) {
  adj[x].push_back(edge{y,c,(int)adj[y].size()});
  adj[y].push_back(edge{x,0,(int)adj[x].size()-1});
}

bool dfs(int x) {
  if (x == target) return 1;
  if (vis[x] == iter) return 0;
  vis[x] = iter;
  for (edge& e: adj[x])
    if (e.capacity >= cap && dfs(e.dest)) {
      e.capacity -= cap;
      adj[e.dest][e.reversed_index].capacity += cap;
      return 1;
    }
  return 0;
}

int maxflow(int S, int T) {
  cap = MAXC, target = T;
  int flow=0;
  while(cap) {
    while(++iter, dfs(S))
      flow += cap;
    cap /= 2;
  }
  return flow;
}
