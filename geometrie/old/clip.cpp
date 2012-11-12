struct point {
	double x, y;
};
 
const int MAX = 1510
 
struct polygon {
	point p[MAX];
	int n;
	point& operator[](int i) {
	return p[i];
	}
} poly, clipped[2];
 
double normalize;
 
double signedPolygonArea (polygon &p) {
	double a = 0;
	for (int i = 1; i < p.n; ++i)
		a += p[i-1].x * p[i].y - p[i].x * p[i-1].y;
	a += p[p.n-1].x * p[0].y - p[0].x * p[p.n-1].y;
	return a/2;
}
 
void insert (polygon &p, point &a) {
	if (p.n > 0) {
		if (p[p.n-1].x == a.x && p[p.n-1].y == a.y)
			return;
	}
	p[p.n++] = a;
}
double sa (point& a, point& b, point& c) {
	return (a.x * b.y - a.y * b.x + b.x * c.y - b.y * c.x + c.x * a.y - a.x * c.y) * normalize;
}
point intersect (point& p1, point& p2, point& p3, point& p4) {
	double a1 = p2.y - p1.y, b1 = p1.x - p2.x;
	double c1 = p1.x*p2.y - p2.x*p1.y;
	double a2 = p4.y - p3.y, b2 = p3.x - p4.x;
	double c2 = p3.x*p4.y - p4.x*p3.y;
 
	double d = a1*b2 - a2*b1;
	point p;
	p.x = (c1*b2 - c2*b1)/d;
	p.y = (a1*c2 - a2*c1)/d;
 
	return p;
}
void doclipping (point& a, point& b, polygon& input, polygon& output) {
	output.n = 0;
	for (int k = 0; k < input.n; ++k) {
		int i = k, ipp = (k+1) % input.n;
		double sai = sa (a, b, input[i]);
		double saipp = sa (a, b, input[ipp]);
	 
		if (sai >= 0 && saipp >= 0) {
			insert (output, input[ipp]);
		} else if (sai >= 0 && saipp < 0) {
			point c = intersect (a, b, input[i], input[ipp]);
			insert (output, c);
		} else if (sai < 0 && saipp >= 0) {
			point c = intersect (a, b, input[i], input[ipp]);
			insert (output, c);
			insert (output, input[ipp]);
		} else {
			assert (sai < 0 && saipp < 0);
		}
	}
}
int main () {
	int currentclipped = 0;
	// TODO here:
	// input polygon into both poly and clipped[0] !!
 
	// normalize the direction of the points of the polygon
	normalize = signedPolygonArea (poly);
	if (normalize > 0) normalize = 1; else normalize = -1;
	for (int i = 0; i < poly.n-1; ++i) {
		doclipping (poly[i], poly[i+1], clipped[currentclipped], clipped[1-currentclipped]);
		currentclipped = 1-currentclipped;
	}
	doclipping (poly[poly.n-1], poly[0], clipped[currentclipped], clipped[1-currentclipped]);
	currentclipped = 1-currentclipped;
	return 0;
}
