// run time: O(n * min(ans^2, |E|)), where n is the size of the left side
vector<int> adj[1001]; // adjacency list
int iter, match[1001], vis[1001];
bool dfs(int x) {
    if (vis[x] == iter) return 0;
    vis[x] = iter;
    for (auto y : adj[x]) {
        if (match[y] < 0 || dfs(match[y])) {
            match[y] = x, match[x] = y;
            return 1;
        }
    }
    return 0;
}
int kuhn(int n) { // n = nodes on left side (numbered 0..n-1)
    memset(match,-1,sizeof match) ;// to accelerate, initialize with a greedy matching
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ++iter;
        ans += dfs(i);
    }
    return ans;
}
