// Runtime O(N+Q), offline algorithm.
const int maxn 110000;
struct node {
	int data,next,answer;
} edge[maxn],query[maxn];
int index_edge[maxn],dset[maxn],father[maxn],index_query[maxn];
int top_edge,top_query;
int tc,n,m,a,b,root;
bool check[maxn];
void init() {
	top_edge = 0, top_query = 0;
	memset(index_edge,0,sizeof(index_edge));
	memset(index_query,0,sizeof(index_query));
	memset(father,0,sizeof(father));
	memset(dset,0,sizeof(dset));
	memset(check,0,sizeof(check));
} // add a tree edge
void add_edge(int u,int v) {
	edge[++top_edge].data = v;
	edge[top_edge].next = index_edge[u];
	index_edge[u] = top_edge;
} // add a query, each query should be added twice, each time for a node.
void add_query(int u,int v) {
	query[++top_query].data = v;
	query[top_query].answer = -1;
	query[top_query].next = index_query[u];
	index_query[u] = top_query;
} // union-find
int find(int r) {
	return dset[r]?dset[r]=find(dset[r]):r;
} // dfs the tree and find the answer for all queries
void dfs(int r) {
	int p = index_edge[r];
	while (p!=0) {
		dfs(edge[p].data);
		dset[find(edge[p].data)] = r;
		p = edge[p].next;
	}
	int q = index_query[r];
	while (q!=0) {
		if (check[query[q].data] || query[q].data == r)
			query[q].answer = find(query[q].data);
		q = query[q].next;
	}
	check[r] = true;
}
/* If we know the root, the process used to find the root can be deleted and
 * the example showed in main() can be simplified. */
int main() {
	init();
	scanf("%d",&n);
	for (int i = 1;i<n;++i) {
		scanf("%d%d",&a,&b); 	// here assume a is the father of b
		father[b] = a; 			// set father, for searching the root later
		add_edge(a,b);
	}
	scanf("%d",&m);
	for (int i=1;i<=m;++i) {
		scanf("%d%d",&a,&b);
		add_query(a,b);			// add query to node a
		add_query(b,a);			// add query to node b
	}
	root = 1;
	while (father[root]!=0) root = father[root];	// find the root
	dfs(root);				// dfs the tree and get the answers of LCA
	for (int i = 1; i<= top_query;i+=2)
		printf("%d\n",max(query[i].answer,query[i+1].answer));
}
