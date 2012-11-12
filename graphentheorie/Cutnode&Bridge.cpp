#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;
#define maxn 10010
#define maxm 50010

int ans;

struct edge {
	int data,next;
	bool bridge;		//if this edge is a bridge
}	_dedges[maxm];
int _dgraph[maxn], _dtp;		//adjacency list
int _dc[maxn];			//color of nodes
int _dd[maxn];			//deep of nodes in the DFS tree
int _da[maxn];			//finishing time of visiting nodes
int _dancestor[maxn];		//depth of highest ancestors of node k and its subnodes
int _dstack[maxn];		//save the nodes in a component
bool _dcut[maxn];			//if this node is a cut node
int _dtimer;			//time record
int _dtop;			//top of stack
int _dcomponent;			//number of component
int _droot;			//root of the DFS tree
void addedge(int u,int v)//add directed edge, treat undirected edge as 2 directed edges
{_dedges[_dtp].data=v; _dedges[_dtp].next=_dgraph[u]; _dedges[_dtp].bridge=false; _dgraph[u]=_dtp++;}
void init (int DFS_root) {
	memset(_dgraph,-1,sizeof(_dgraph)); _dtp = 0; //empty the graph
	memset(_dancestor,0x7f,sizeof(_dancestor));
	memset(_dc,0,sizeof(_dc));
	memset(_dcut,0,sizeof(_dcut));
	_dtimer = 0;			//the time we've finished visiting a node
	_dtop = 0;				//empty the stack
	_dcomponent = 0;				//reset the number of component
	_droot = DFS_root;             //XXX set the root, make no sense for SCC
}
void DFS(int k, int father, int deep) {
	int tot,p,now;
	_dc[k] = 1;  			//state of node, 0 not checked, 1 checking, 2 checked
	_dd[k] = deep; 			//depth of nodes in the DFS tree
//	_dancestor[k] = deep, tot = 0;  	//(1)
//	_dstack[_dtop++] = k;		//(3)
	p = _dgraph[k];
	while (p!=-1) {
		now = _dedges[p].data;
		if (now != father)	{//(1)*** comment this line for Point for SCC (c)
//		if (_dc[now] == 1)							//(1)
//			_dancestor[k] = min(_dancestor[k], _dd[now]);				//(1)
		}//(1)*** comment this line for Point for SCC (c) !
		if (_dc[now] == 0) {
			DFS(now,k,deep+1);
//			tot = tot+1, _dancestor[k] = min(_dancestor[k], _dancestor[now]);	//(1)
//			if ((k==_droot && tot>1) || (k!=_droot && _dancestor[now]>=_dd[k]))	//(1)
//                _dcut[k] = true;					//(1)
//			if (_dancestor[now]>_dd[k]) _dedges[p].bridge = true;			//(2)
		}
		p = _dedges[p].next;
	}
//	if (_dancestor[k]==_dd[k]) {			//(3)
//		_dcomponent++;				//(3)
//		do {					//(3)
//			cout<<_dstack[--_dtop]<<endl;  	//(3) handle nodes in a component
//		}	while (_dstack[_dtop] != k);	//(3)
//	}						//(3)
	_dc[k] = 2;
	_da[k] = ++_dtimer;
}
/*A)cancel the comment marked with (1) we get the algorithm of cut nodes
B)cancel the comment marked with (1) and (2) we get the algorithm of bridges
C)cancel the comment marked with (1)(the line with *** should be commented) and (3)
	we get the algorithm of strongly connected components for directed graph
D)cancel the comment marked with (1) and (3) we get the algorithm of biconnected
	components for undirected graph
E)something else: algorithm of Kosaraju: Use the algotihm above to get the time record
array a, and then dfs each node k according to a[k] from biggest to smallest in the
reverse graph, each component we get is a strongly connected component.
F)2-sat: Construct the graph according to the constraints with 2n nodes. By
compressing each strongly connected component to a node and reversing all the edges
we get a DAG, then get the topological order of this DAG. Each time we select a node
that is legal according to the topological order, mark it as chosen and its paradoxical
node(if element X is in node V then the node contains -X is V's paradoxical node) as illegal.
At last all the compressed elements in the chosen node are the ones we want to choose*/
