// Get the kernel of polygon, Runtime (n*log(n))
// Need cstdio, cmath, vector, algorithm. Two points a&b present a halfplane on
// the left side of vector a->b.
const double eps=1e-10, PI=acos(-1.0);
const int mn=3010;
#define mp(A,B) make_pair(A,B)
#define pb(X) push_back(X)
#define clr(x) memset(x,0,sizeof(x))
struct point{ double x,y; };
struct polygon { int size; point p[mn]; };
struct line { point a,b; };
double at2[mn];
int ord[mn],dq[mn+1],n;
vector< line > ls; //-> Set of halfplanes, read in here
line tl;
polygon pg; //-> Answer is stored here
// Sign function
inline int sig(double k) {
	return (k < -eps)? -1: k > eps;
} // Cross product of vector (p0,p1) and (p0,p2)
inline double multi(point p0, point p1, point p2) {
	return ( p1.x - p0.x )*( p2.y - p0.y )
		-( p2.x - p0.x )*( p1.y - p0.y );
} // Get the intersection point of (s1,e1) and (s2,e2)
void isIntersected(point s1, point e1, point s2, point e2, point &pp) {
	double dot1,dot2;
	dot1=multi(s2,e1,s1); dot2=multi(e1,e2,s1);
	pp.x=(s2.x*dot2 + e2.x*dot1) / (dot2+dot1);
	pp.y=(s2.y*dot2 + e2.y*dot1) / (dot2+dot1);
} // Compare function according polar angle in [-PI, PI)
inline bool cmp(int u,int v) {
	if(sig(at2[u]-at2[v])==0)return multi(ls[v].a,ls[v].b,ls[u].b)>=0;
	return at2[u]<at2[v];
} // Check if the intersection point of two half-planes is ontside the third
bool judgein(int x,int y,int z) {
	point pnt;
	isIntersected(ls[x].a, ls[x].b, ls[y].a, ls[y].b, pnt);
	return  sig(multi(ls[z].a,ls[z].b,pnt))<0;
} // Get the intersection of half-planes
void HalfPlaneIntersection() {
	int n=ls.size(),tmpn,i;
	pg.size = 0;
	for(int i=0;i<n;i++) {
		at2[i]=atan2( ls[i].b.y-ls[i].a.y, ls[i].b.x-ls[i].a.x);
		ord[i]=i;
	}
	sort(ord,ord+n,cmp);
	for (i = 1 , tmpn = 1 ; i < n ; i++)
		if(sig(at2[ord[i-1]]-at2[ord[i]])!=0)ord[tmpn++]=ord[i];
	int n0 = tmpn;
	int bot=1,top=bot+1;
	dq[bot]=ord[0];dq[top]=ord[1];
	for(int i=2;i<n0;i++) {
		while(bot<top && judgein(dq[top-1],dq[top],ord[i])) top--;
		while(bot<top && judgein(dq[bot+1],dq[bot],ord[i])) bot++;
		if (top==bot) {
			if (sig(fabs(at2[dq[top]]-at2[ord[i]])-PI)==0) return;
			if (judgein(dq[top],ord[i],dq[top+1])) return;
		}
		dq[++top]=ord[i];
	}
	bool f = true;
	while (f) {
		f = false;
		while(bot<top && judgein(dq[top-1],dq[top],dq[bot]))f|=1,top--;
		while(bot<top && judgein(dq[bot+1],dq[bot],dq[top]))f|=1,bot++;
	}
	dq[--bot]=dq[top];
	for (int i=bot+1;i<=top;i++)
		isIntersected(ls[dq[i-1]].a,ls[dq[i-1]].b,ls[dq[i]].a,ls[dq[i]].b,
				pg.p[pg.size++]);
	for (i=1,tmpn=1;i<pg.size;++i)
		if (sig(pg.p[i].x-pg.p[i-1].x)!=0 || sig(pg.p[i].y-pg.p[i-1].y)!=0)
			pg.p[tmpn++]=pg.p[i];
	while (tmpn>2 && sig(pg.p[tmpn-1].x-pg.p[0].x)==0 &&
			sig(pg.p[tmpn-1].y-pg.p[0].y)==0) tmpn--;
	pg.size = tmpn;
}
