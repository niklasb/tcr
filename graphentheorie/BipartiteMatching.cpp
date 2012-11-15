const int mn1 = 501, mn2 = 501;
struct node {
	int v;
	node *next;
}*g[mn1], pool[mn1 * mn2];
int pp;
bool succeed(int v, bool *mx, int *pre, bool *vis) {
	for (node *i = g[v]; i; i = i->next)
		if (!vis[i->v]) {
			vis[i->v] = 1;
			if (pre[i->v] == -1 || succeed(pre[i->v], mx, pre, vis))
				return pre[i->v] = v, mx[v] = 1, 1;
		}
	return 0;
}
/*	n1, n2: the number of vertices on the left/right
	bool mx[i = 0..mn1-1]: whether vertex i on the left has been matched
	int pre[i = 0..mn2-1]: the vertex on the left matching i on the right. -1 if not matched */
int hungarian(int n1, int n2, bool *mx, int *pre) {
	memset(mx, 0, sizeof(mx[0]) * n1);
	memset(pre, -1, sizeof(pre[0]) * n2);
	int ans = 0;
	for (int i = 0; i < n1; i++) //use greedy to get an initial matching
		for (node *p = g[i]; !mx[i] && p; p = p->next)
			if (pre[p->v] == -1) mx[i] = 1, pre[p->v] = i, ans++;
	static bool vis[mn2];
	for (int i = 0; i < n1 && ans < n1; i++)
		if (!mx[i]) {
			memset(vis, 0, sizeof(vis[0]) * n2);
			if (succeed(i, mx, pre, vis)) ans++;
		}
	return ans;
}
