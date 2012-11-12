#include <cmath>
 
#define MAX 1024
#define EPS 1e-7
 
struct point {
    double x, y;
};
 
struct polygon {
    int n;
    point p[MAX];
    point &operator[](int i) {
        return p[i];
    }
};
 
inline double dist(const point &a, const point &b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}
 
bool contains(polygon &P, point &p) {
    bool inside = false;
 
    for (int j = P.n - 1, i = 0; i < P.n; j = i++) {
        if (fabs(dist(p, P[j]) + dist(p, P[i]) - dist(P[j], P[i])) < EPS) {
            return true; // true = Rand gehoert mit zum Polygon
        }
 
        if (min(P[j].y, P[i].y) <= p.y && max(P[j].y, P[i].y) > p.y &&
            (p.y - P[j].y) * (P[i].x - P[j].x) / (P[i].y - P[j].y) > p.x - P[j].x) {
            inside = !inside;
        }
    }
    return inside;
}
