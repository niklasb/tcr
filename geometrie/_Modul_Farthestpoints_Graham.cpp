/* Runtime: O(n*log(n)). Find 2 farthest points in a set of points.
 * Use graham algorithm to get the convex hull.
 * Note: In extreme situation, when all points coincide, the program won't work
 * probably. A prejudge of this situation may consequently be needed */
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int mn = 100005;
const double pi = acos(-1.0), eps = 1e-5;
struct point { double x, y; } a[mn];
int n, cn, st[mn];
inline bool cmp(const point &a, const point &b) {
	if (a.y != b.y) return a.y < b.y; return a.x < b.x;
}
inline int dblcmp(const double &d) {
	if (abs(d) < eps) return 0; return d < 0 ? -1 : 1;
}
inline double cross(const point &a, const point &b, const point &c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
inline double dis(const point &a, const point &b) {
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
} // get the convex hull
void graham_scan() {
	sort(a, a + n, cmp);
	cn = -1;
	st[++cn] = 0;
	st[++cn] = 1;
	for (int i = 2; i < n; i++) {
		while (cn>0 && dblcmp(cross(a[st[cn-1]],a[st[cn]],a[i]))<=0) cn--;
		st[++cn] = i;
	}
	int newtop = cn;
	for (int i = n - 2; i >= 0; i--) {
		while (cn>newtop && dblcmp(cross(a[st[cn-1]],a[st[cn]],a[i]))<=0) cn--;
		st[++cn] = i;
	}
}
inline int next(int x) { return x + 1 == cn ? 0 : x + 1; }
inline double angle(const point &a,const point &b,const point &c,const point &d){
	double x1 = b.x - a.x, y1 = b.y - a.y, x2 = d.x - c.x, y2 = d.y - c.y;
	double tc = (x1 * x2 + y1 * y2) / dis(a, b) / dis(c, d);
	return acos(abs(tc) > 1.0 ? (tc > 0 ? 1 : -1) * 1.0 : tc);
}
void maintain(int &p1, int &p2, double &nowh, double &nowd) {
	nowd = dis(a[st[p1]], a[st[next(p1)]]);
	nowh = cross(a[st[p1]], a[st[next(p1)]], a[st[p2]]) / nowd;
	while (1) {
		double h = cross(a[st[p1]], a[st[next(p1)]], a[st[next(p2)]]) / nowd;
		if (dblcmp(h - nowh) > 0) {
			nowh = h;
			p2 = next(p2);
		} else break;
	}
}
double find_max() {
	double suma = 0, nowh = 0, nowd = 0, ans = 0;
	int p1 = 0, p2 = 1;
	maintain(p1, p2, nowh, nowd);
	while (dblcmp(suma - pi) <= 0) {
		double t1 = angle(a[st[p1]], a[st[next(p1)]], a[st[next(p1)]],
				a[st[next(next(p1))]]);
		double t2 = angle(a[st[next(p1)]], a[st[p1]], a[st[p2]],a[st[next(p2)]]);
		if (dblcmp(t1 - t2) <= 0) {
			p1 = next(p1); suma += t1;
		} else {
			p1 = next(p1); swap(p1, p2); suma += t2;
		}
		maintain(p1, p2, nowh, nowd);
		double d = dis(a[st[p1]], a[st[p2]]);
		if (d > ans) ans = d;
	}
	return ans;
}
int main() {
	while (scanf("%d", &n) != EOF && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		if (n == 2)
			printf("%.2lf\n", dis(a[0], a[1]));
		else {
			graham_scan();
			double mx = find_max();
			printf("%.2lf\n", mx);
		}
	}
	return 0;
}