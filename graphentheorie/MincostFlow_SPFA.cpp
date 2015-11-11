typedef long long Captype;        // set capacity type (long long or int)
// for Valtype double, replace clr(dis,0x7f) and use epsilon for distance comparison
typedef long long Valtype;        // set type of edge weight (long long or int)
static const Captype flowlimit = 1LL<<60;    // should be bigger than maxflow
struct MinCostFlow {            //XXX Usage: class should be created by new.
static const int maxn = 450;                 // number of nodes, should be bigger than n
static const int maxm = 5000;              // number of edges
struct edge {
    int node,next; Captype flow; Valtype value;
}   edges[maxm<<1];
int graph[maxn],queue[maxn],pre[maxn],con[maxn],n,m,source,target,top;
bool inq[maxn];
Captype maxflow;
Valtype mincost,dis[maxn];
MinCostFlow() { memset(graph,-1,sizeof(graph)); top = 0; }
inline int inverse(int x) {return 1+((x>>1)<<2)-x; }
inline int addedge(int u,int v,Captype c, Valtype w) { // add a directed edge
    edges[top].value = w; edges[top].flow = c; edges[top].node = v;
    edges[top].next = graph[u]; graph[u] = top++;
    edges[top].value = -w; edges[top].flow = 0; edges[top].node = u;
    edges[top].next = graph[v]; graph[v] = top++;
    return top-2;
}
bool SPFA() { // Bellmanford, also works with negative edge weight.
    int point, nod, now, head = 0, tail = 1;
    memset(pre,-1,sizeof(pre));
    memset(inq,0,sizeof(inq));
    memset(dis,0x7f,sizeof(dis));
    dis[source] = 0; queue[0] = source; pre[source] = source; inq[source] = true;
    while (head!=tail) {
        now = queue[head++]; point = graph[now]; inq[now] = false; head %= maxn;
        while (point != -1) {
            nod = edges[point].node;
            // use epsilon here for floating point comparison to avoid loops
            if (edges[point].flow>0 && dis[nod]>dis[now]+edges[point].value) {
                dis[nod] = dis[now] + edges[point].value;
                pre[nod] = now;
                con[nod] = point;
                if (!inq[nod]) {
                    inq[nod] = true;
                    queue[tail++] = nod;
                    tail %= maxn;
                }
            }
            point = edges[point].next;
        }
    }
    return pre[target]!=-1; //&& dis[target]<=0; //for min-cost max-flow
}
void extend()
{
    Captype w = flowlimit;
    for (int u = target; pre[u]!=u; u = pre[u])
        w = min(w, edges[con[u]].flow);
    maxflow += w;
    mincost += dis[target]*w;
    for (int u = target; pre[u]!=u; u = pre[u]) {
        edges[con[u]].flow-=w;
        edges[inverse(con[u])].flow+=w;
    }
}
void mincostflow() {
    maxflow = 0; mincost = 0;
    while (SPFA()) extend();
}};
