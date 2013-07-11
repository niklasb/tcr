// run time: O(n * min(ans^2, |E|)), where n is the size of the left side
vector<int> madj[1001]; // adjacency list
int pairs[1001]; // for every node, stores the matching node on the other side or -1
bool vis[1001];
bool dfs(int i) {
    if (vis[i]) return 0;
    vis[i] = 1;
    foreach(it,madj[i]) {
        if (pairs[*it] < 0 || dfs(pairs[*it])) {
            pairs[*it] = i, pairs[i] = *it;
            return 1;
        }
    }
    return 0;
}
int kuhn(int n) { // n = nodes on left side (numbered 0..n-1)
    clr(pairs,-1);
    int ans = 0;
    rep(i,0,n) {
        clr(vis,0);
        ans += dfs(i);
    }
    return ans;
}
