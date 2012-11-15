const int mn1 = 501, mn2 = 501;
struct node {
	int v;
	node *next;
}*g[mn1], pool[mn1 * mn2];
int pp;
bool succeed(int v, int *mx, int *my, bool *vis) {
    for (node *i = g[v]; i; i = i->next)
        if (!vis[i->v]) {
            vis[i->v] = 1;
            if (my[i->v] == -1 || succeed(my[i->v], mx, my, vis))
                return mx[v] = i->v, my[i->v] = v, 1;
        }
    return 0;
}/* n1, n2: the number of vertices on the left/right
    int mx[i = 0..mn1-1]: the vertex on the right matching i on the left. -1 if not matched
    int my[i = 0..mn2-1]: the vertex on the left matching i on the right. -1 if not matched */
int hungarian(int n1, int n2, int *mx, int *my) {
    memset(mx, -1, sizeof(mx[0]) * n1);
    memset(my, -1, sizeof(my[0]) * n2);
    int ans = 0;
    for (int i = 0; i < n1; i++) //use greedy to get an initial matching
        for (node *p = g[i]; mx[i] == -1 && p; p = p->next)
            if (my[p->v] == -1) mx[i] = p->v, my[p->v] = i, ans++;
    static bool vis[mn2];
    for (int i = 0; i < n1 && ans < n1; i++)
        if (mx[i] == -1) {
            memset(vis, 0, sizeof(vis[0]) * n2);
            if (succeed(i, mx, my, vis)) ans++;
        }
    return ans;
}
