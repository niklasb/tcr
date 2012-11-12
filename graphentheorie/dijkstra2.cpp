const int mn = 50005, inf = 0x3f3f3f3f;
typedef vector<int> VINT;
struct heapcomp{
	int *ref;
	heapcomp(int *r) : ref(r) { }
	bool operator()(int a, int b) {	return ref[a] > ref[b];	}
};
int dijkstra(int n, const VINT g[], const VINT c[], int s, int t, int *dis,	int *pre) {
	static int h[mn], sz;
	for (int i = 0; i < n; ++i) dis[i] = inf, pre[i] = -1;
	dis[s] = 0, sz = 1, h[0] = s;
	heapcomp cmp(dis);
	while (sz > 0) {
		int top = h[0];
		pop_heap(h, h + sz--, cmp);
		if (top == t) return dis[top];
		for (size_t i = 0; i < g[top].size(); ++i) {
			if (dis[g[top][i]] > dis[top] + c[top][i]) {
				dis[g[top][i]] = dis[top] + c[top][i];
				pre[g[top][i]] = top;
				h[sz++] = g[top][i];
				push_heap(h, h + sz, cmp);
			}
		}
	}
	return -1;
}