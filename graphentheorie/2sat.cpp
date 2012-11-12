//2-SAT
// First find all SCCs. No solution if x and ~x are in one component.
// Compress all SCCs to single nodes. Build reversed DAG.
// Coloring according to the toposort, find one un-colored node, color it RED.
// All nodes and their succedents in contrary with x are colered BLUE.
// Do until all nodes are colored. The red ones build a solution to the 2-SAT.
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 16010;//2*8000
char color[MAXN];// coloring
bool visit[MAXN];
queue<int> q1,q2;
vector< vector<int> > adj; //origional graph
vector< vector<int> > radj;//reversed graph
vector< vector<int> > dag; //the reversed DAG after compression
int n,m,cnt,id[MAXN],order[MAXN],ind[MAXN];//SCC, visiting order, in-degree

void dfs(int u){
    visit[u]=true;
    int i,len=adj[u].size();
    for(i=0;i<len;i++)
        if(!visit[adj[u][i]]) dfs(adj[u][i]);
    order[cnt++]=u;
}
void rdfs(int u){
    visit[u]=true; id[u]=cnt;
    int i,len=radj[u].size();
    for(i=0;i<len;i++)
        if(!visit[radj[u][i]]) rdfs(radj[u][i]);
}
void korasaju(){
    int i;
    memset(visit,false,sizeof(visit));
    for(cnt=0,i=1;i<=2*n;i++) if(!visit[i]) dfs(i);
    memset(id,0,sizeof(id));
    memset(visit,false,sizeof(visit));
    for(cnt=0,i=2*n-1;i>=0;i--)
        if(!visit[order[i]]) cnt++,rdfs(order[i]);
}
bool solvable(){
    for(int i=1;i<=n;i++)
        if(id[2*i-1]==id[2*i]) return 0;
    return 1;
}
void topsort(){
    int i,j,len,now,p,pid;
    while(!q1.empty()){
        now=q1.front();  q1.pop();
        if(color[now]!=0) continue ;
        color[now]='R';  ind[now]=-1;
        for(i=1;i<=2*n;i++){
            if(id[i]==now){
                p=(i%2)?i+1:i-1;   pid=id[p];   q2.push(pid);
                while(!q2.empty()){
                    pid=q2.front(); q2.pop();
                    if(color[pid]=='B') continue ;
                    color[pid]='B';
                    int len=dag[pid].size();
                    for(j=0;j<len;j++) q2.push(dag[pid][j]);
                }
            }
        }
        len=dag[now].size();
        for(i=0;i<len;i++){
            ind[dag[now][i]]--;
            if(ind[dag[now][i]]==0) q1.push(dag[now][i]);
        }
    }
}
int main(){
    int i,j,x,y,xx,yy,len;
    while(scanf("%d %d",&n,&m)!=EOF){
        adj.assign(2*n+1,vector<int>());
        radj.assign(2*n+1,vector<int>());
        for(i=0;i<m;i++){
            scanf("%d %d",&x,&y);
            xx=(x%2)?x+1:x-1;       yy=(y%2)?y+1:y-1;
            adj[x].push_back(yy);   adj[y].push_back(xx);
            radj[yy].push_back(x);  radj[xx].push_back(y);
        }
        korasaju();
        if(!solvable()) puts("NIE");
        else{
            dag.assign(cnt+1,vector<int>());
            memset(ind,0,sizeof(ind));
            memset(color,0,sizeof(color));
            for(i=1;i<=2*n;i++){
                len=adj[i].size();
                for(j=0;j<len;j++)
                    if(id[i]!=id[adj[i][j]]){
                        dag[id[adj[i][j]]].push_back(id[i]);
                        ind[id[i]]++;
                    }
            }
            for(i=1;i<=cnt;i++) if(ind[i]==0) q1.push(i);
            topsort();
            for(i=1;i<=n;i++){
                if(color[id[2*i-1]]=='R') printf("%d\n",2*i-1);
                else printf("%d\n",2*i);
            }
        }
    }
    return 0;
}
