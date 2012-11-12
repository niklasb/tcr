// Get convex hull in 3 dimension space. Runtime(n^2)
#include <cstdio>
#include <cmath>
#include <algorithm>
#define eps 1e-7
#define MAXV 1305
using namespace std;
struct pt{ // point in 3 dimesions
	double x, y, z;
	pt(){}
	pt(double _x, double _y, double _z): x(_x), y(_y), z(_z){}
	pt operator-(const pt p1){return pt(x - p1.x, y - p1.y, z - p1.z);}
	pt operator*(pt p){return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}	//cross
	double operator^(pt p){return x*p.x+y*p.y+z*p.z;}			// dot product
};
struct _3DCH{
	struct fac{
		int a, b, c;  //3 points in a face
		bool ok;	  //indicates if this face belongs to the final convex hull.
	};
	int n;		//initial number of points
	pt P[MAXV];	//initial points
	int cnt;	//number of triangles on the face of convex hull
	fac F[MAXV*8]; //triangles on the face of convex hull
	int to[MAXV][MAXV];
	double vlen(pt a){return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);} //length of vector
	double area(pt a, pt b, pt c){return vlen((b-a)*(c-a));} //2*triangle area
	double volume(pt a,pt b,pt c,pt d){return (b-a)*(c-a)^(d-a);}//6*Tetrahedron volume
	double ptof(pt &p, fac &f){ //positive if on the same side
		pt m = P[f.b]-P[f.a], n = P[f.c]-P[f.a], t = p-P[f.a];
		return (m * n) ^ t;
	}
	void deal(int p, int a, int b){
		int f = to[a][b];
		fac add;
		if (F[f].ok){
			if (ptof(P[p], F[f]) > eps) dfs(p, f);
			else {
				add.a = b, add.b = a, add.c = p, add.ok = 1;
				to[p][b] = to[a][p] = to[b][a] = cnt;
				F[cnt++] = add;
			}
		}
	}
	void dfs(int p, int cur) {
		F[cur].ok = 0;
		deal(p, F[cur].b, F[cur].a);
		deal(p, F[cur].c, F[cur].b);
		deal(p, F[cur].a, F[cur].c);
	}
	bool same(int s, int t) {
		pt &a = P[F[s].a], &b = P[F[s].b], &c = P[F[s].c];
		return fabs(volume(a, b, c, P[F[t].a])) < eps && fabs(volume(a, b, c,
				P[F[t].b])) < eps && fabs(volume(a, b, c, P[F[t].c])) < eps;
	}
	void construct() { // Construct convex hull. It is he method to be called.
		cnt = 0;
		if (n < 4) return;
		/****this code is to make sure the first 4 points are not coplanar,
		 * can be deleted if it is already garanteed*****/
		bool sb = 1;
		for (int i = 1; i < n; i++){ //make sure first 2 points aren't concurrent.
			if (vlen(P[0] - P[i]) > eps){ swap(P[1], P[i]); sb = 0; break; }}
		if (sb)return;
		sb = 1;
		for (int i = 2; i < n; i++){ //make sure first 3 points are not colinear.
			if (vlen((P[0] - P[1]) * (P[1] - P[i])) > eps)
				{ swap(P[2], P[i]);sb = 0;break;}}
		if (sb)return;
		sb = 1;
		for (int i = 3; i < n; i++){ //make sure first 4 points are not coplanar.
			if (fabs((P[0] - P[1]) * (P[1] - P[2]) ^ (P[0] - P[i])) > eps)
				{ swap(P[3], P[i]);sb = 0;break;}}
		if (sb)return;
		/*to make sure the first 4 points are not coplanar, can be deleted(above)*/
		fac add;
		for (int i = 0; i < 4; i++){
			add.a = (i+1)%4, add.b = (i+2)%4, add.c = (i+3)%4, add.ok = 1;
			if (ptof(P[i], add) > 0)
				swap(add.b, add.c);
			to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
			F[cnt++] = add;
		}
		for (int i = 4; i < n; i++)
			for (int j = 0; j < cnt; j++)
				if (F[j].ok && ptof(P[i], F[j]) > eps){
					dfs(i, j);
					break;
				}
		int tmp = cnt;
		cnt = 0;
		for (int i = 0; i < tmp; i++)
			if (F[i].ok) F[cnt++] = F[i];
	}
	double area() { //surface area
		double ret = 0.0;
		for (int i = 0; i < cnt; i++)
			ret += area(P[F[i].a], P[F[i].b], P[F[i].c]);
		return ret / 2.0;
	}
	double volume() { //volume
		pt O(0, 0, 0);
		double ret = 0.0;
		for (int i = 0; i < cnt; i++)
			ret += volume(O, P[F[i].a], P[F[i].b], P[F[i].c]);
		return fabs(ret / 6.0);
	}
	int facetCnt_tri() {return cnt;} //number of triangles on the face.
	int facetCnt() { //number of faces.
		int ans = 0;
		for (int i = 0; i < cnt; i++){
			bool nb = 1;
			for (int j = 0; j < i; j++)	if (same(i, j)){ nb = 0; break;}
			ans += nb;
		}
		return ans;
	}
};
_3DCH hull; /**Read data in hull.n and hull.p, call hull.construct() **/