#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
const double EPS = 1e-10;
const double INF = 1e100;
const int maxn = 1510;
const double PI = acos(-1.0);
const double E = exp(1.0);
const double EULER = 0.57721566490153286;
// change -0.00 to 0.00, d is the number of digits after dot.
inline double fix_negative(double x, int d) {
	static char s[40]; sprintf(s,"%.*lf",d,x);
	return strpbrk(s, "123456789") ? x : 0;
}
// sign function
inline int sgn(const double &x) { return x<-EPS?-1:x>EPS; }
struct Point { // point in 2D space
    double x,y;
    Point(): x(0.0),y(0.0) {};
    Point(double x0,double y0): x(x0),y(y0) {};
    Point operator+ (const Point &p) const {return Point(x+p.x,y+p.y);}
    Point operator- (const Point &p) const {return Point(x-p.x,y-p.y);}
    Point operator* (double k) const {return Point(x*k,y*k);}
    Point operator/ (double k) const {return Point(x/k,y/k);}
    bool operator< (const Point &p) const {return sgn(x-p.x)?x+EPS<p.x:y+EPS<p.y;}
    bool operator> (const Point &p) const {return sgn(x-p.x)?x>p.x+EPS:y>p.y+EPS;}
    bool operator== (const Point &p) const {return !(sgn(x-p.x) || sgn(y-p.y));}
}; // point in 3D space
struct Point3D {
	double x,y,z;
	Point3D(): x(0.0),y(0.0),z(0.0) {};
	Point3D(double x0,double y0, double z0): x(x0),y(y0),z(z0) {};
	Point3D operator+ (const Point3D &p) const {return Point3D(x+p.x,y+p.y,z+p.z);}
	Point3D operator- (const Point3D &p) const {return Point3D(x-p.x,y-p.y,z-p.z);}
	Point3D operator* (double k) const {return Point3D(x*k,y*k,z*k);}
	Point3D operator/ (double k) const {return Point3D(x/k,y/k,z/k);}
    double len2() const { return x * x + y * y + z * z; }
    double len() const { return sqrt(len2()); }
    Point3D tolen(double l) const { double len = l/sqrt(len2());
    	return Point3D(x * len, y * len, z * len);}
}; // length of cross product of vector p1-p0 and p2-p0
inline double cross(const Point &p0,const Point &p1,const Point &p2) {
    return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
} // cross product of vector p0 and p1 in 3D space
inline Point3D cross(const Point3D &p0, const Point3D &p1) {
	return Point3D(p0.y*p1.z-p0.z*p1.y,p0.z*p1.x-p0.x*p1.z,p0.x*p1.y-p0.y*p1.x);
} // cross product of vector p1-p0 and p2-p0 in 3D space
inline Point3D cross(const Point3D &p0, const Point3D &p1, const Point3D &p2) {
	return cross(p1-p0,p2-p0);
} // dot product of vector p1-p0 and p2-p0
inline double dot(const Point &p0,const Point &p1,const Point &p2) {
    return (p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
} // mixed product of vector p1-p0, p2-p0 and p3-p0 in 3D space
inline double mixed(Point3D p0, Point3D p1, Point3D p2, Point3D p3) {
	p1=p1-p0; p2=p2-p0; p3=p3-p0;
	return p1.x*p2.y*p3.z+p2.x*p3.y*p1.z+p3.x*p1.y*p2.z
			-p3.x*p2.y*p1.z-p2.x*p1.y*p3.z-p1.x*p3.y*p2.z;
} // distance between points p1 and p2
inline double dist(const Point &p1, const Point &p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
} // pedal(Lot) of point p to line (p0,p1)
Point pedal(const Point &p0, const Point &p1, const Point &p) {
	double A = p1.y-p0.y;
	double B = p0.x-p1.x;
	double C = p1.x*p0.y-p0.x*p1.y;// change line(p0,p1) in form Ax+By+C=0
	double D = A*A+B*B;
	return Point((B*B*p.x-A*B*p.y-A*C)/D,(-A*B*p.x+A*A*p.y-B*C)/D);
} // pedal(Lot) of point p to line (p0,p1) in 3D space
Point3D pedal(const Point3D &p0, const Point3D &p1, const Point3D &p) {
	double u=-((p.x-p0.x)*(p0.x-p1.x)+(p.y-p0.y)*(p0.y-p1.y)+(p.z-p0.z)*(p0.z-p1.z))/
		((p0.x-p1.x)*(p0.x-p1.x)+(p0.y-p1.y)*(p0.y-p1.y)+(p0.z-p1.z)*(p0.z-p1.z));
	return Point3D(p0.x+(p1.x-p0.x)*u,p0.y+(p1.y-p0.y)*u,p0.z+(p1.z-p0.z)*u);
} // pedal(Lot) of point p to plane(p0,p1,p2)
Point3D pedal(Point3D p0, Point3D p1, Point3D p2, Point3D p) {
	Point3D u1=p1-p0, u2=p2-p0;
	double A = u1.y*u2.z-u2.y*u1.z;
	double B = u1.z*u2.x-u2.z*u1.x;
	double C = u1.x*u2.y-u2.x*u1.y;
	double D = -A*p0.x-B*p0.y-C*p0.z; //change plane (p0,p1,p2) to Ax+By+Cz+D=0
	double E = A*A+B*B+C*C;
	return p-Point3D(A,B,C)*(A*p.x+B*p.y+C*p.z+D)/E;
}  // convert line x=p+tu to Ax+By+C=0 representation
void fromVector(Point p, Point u, double &A, double &B, double &C) {
    A = u.y; B = -u.x; C = cross(u, p, Point());
} // Intersection of lines ax+by+c=0&dx+ey+f=0.
Point intersect(double a,double b,double c,double d,double e,double f, int &num) {
	double temp = b*d-e*a;
	if (sgn(temp)==0) {
		num=sgn(a*f-c*d)==0 && sgn(b*f-c*e)==0?2:0;//num=0 no intersect.num=2 coincide
		return Point();  //in both situations return an invalid point
	}
	num = 1;  //num=1 just one intersection
    return Point((c*e-f*b)/temp,(a*f-c*d)/temp); //return the intersection point
} //intersection of segments [a,b]&[c,d], only if two segments strictly intersect
  // each other in interior, the intersection point will be returned.
Point intersect(Point a,Point b,Point c,Point d,int &cas) {
	double s1,s2,s3,s4;
	int d1,d2,d3,d4;
	d1 = sgn(s1 = cross(a,b,c));
	d2 = sgn(s2 = cross(a,b,d));
	d3 = sgn(s3 = cross(c,d,a));
	d4 = sgn(s4 = cross(c,d,b));
	if ((d1^d2)==-2 && (d3^d4)==-2) {
		cas = 1;  //cas=1 strictly intersect each other in the interior
		return Point((c.x*s2-d.x*s1)/(s2-s1),(c.y*s2-d.y*s1)/(s2-s1));//intersection
	}
	if ((d1==0 && sgn(dot(c,a,b))<=0) ||
		(d2==0 && sgn(dot(d,a,b))<=0) ||
		(d3==0 && sgn(dot(a,c,d))<=0) ||
		(d4==0 && sgn(dot(b,c,d))<=0)) cas = 2;  //cas=2,intersect but no in interior
	else cas = 0; // no intersection
	return Point(); // in the last two situations return an invalid intersection point
} //intersection of circle(R,r)&line Ax+By+C=0, n is the number of intersections
void intersect(Point R, double r, double A, double B, double C, Point *out, int &n) {
	double D = A*A+B*B;
	double sqrtD = sqrt(A*A+B*B);
	double dis = fabs(A*R.x+B*R.y+C)/sqrtD;
	if (sgn(dis-r)==1) { n = 0; return; }
	Point F = Point((B*B*R.x-A*B*R.y-A*C)/D,(-A*B*R.x+A*A*R.y-B*C)/D);
	if (sgn(dis-r)==0) { out[0] = F; n = 1; return; }
	double d = sqrt(r*r-dis*dis);
	out[0].x = F.x+B*d/sqrtD; out[0].y = F.y-A*d/sqrtD;
	out[1].x = F.x-B*d/sqrtD; out[1].y = F.y+A*d/sqrtD;
	if (out[0]>out[1]) swap(out[0],out[1]);
	n = 2;
} // intersection of Circles (R,r) and (S,s), n is the number of intersections
void intersect(Point R, double r,Point S, double s,Point *out, int &n) {
	if ((R==S) && (sgn(r-s)==0)) {
		if (sgn(r)==0) {
			n=1; out[0] = R;
		} else n=-1; // n=-1 if two circles have infinit intersection point
	} else intersect(R, r, 2*(S.x-R.x),2*(S.y-R.y),
			s*s-r*r+R.x*R.x-S.x*S.x+R.y*R.y-S.y*S.y,out,n);
} // area of a simple polygon
double area(Point *in, int n) {
    double res = 0;
    for (int i=1;i<n;++i) res+=in[i].x*in[(i+1)%n].y-in[(i+1)%n].x*in[i].y;
    return fabs(res)/2.0;
} // check if point p is on the segment [p1,p2]
int inSegment(const Point &p1, const Point &p2, Point p) {
    if (p==p1) return 1;
    if (p==p2) return 1; // return 1 if point p is on the endpoint of the segment
    if (sgn(cross(p,p1,p2))==0 && sgn(dot(p,p1,p2))==-1) return 2;//return 2,interior
    return 0; // return 0 if point p is not on the segment
} // check if point p is in the polygon in[0..n-1]
int inPolygon(Point *in, int n, Point p) {
    double angle = 0,temp, al; int k;
    for (int i=0;i<n;++i) {
        temp = cross(p,in[i],in[(i+1)%n]);
        if (sgn(temp)==0) {
            k = inSegment(in[i],in[(i+1)%n],p);
            if (k!=0) return k;	//return 1 on vertex or 2 on border
        }
        al = asin(temp/dist(p,in[i])/dist(p,in[(i+1)%n]));
        angle += sgn(dot(p,in[i],in[(i+1)%n]))>=0?al:al>=0?PI-al:-PI-al;
    }
    if (fabs(angle)<1.0) return 0; else return 3; //return 0 outside or 3 inside polygon
} // The cycle of minimal area that covers all the points in points[0..n-1].
void minimalCycle(Point *points, int n, Point &center, double &radius) {
	static Point p[maxn];
	int randcase=n,x,y;
	for (int i=0;i<n;++i) p[i] = points[i];
	srand((unsigned)time(NULL)); //expected runtime of the algorithm is O(n)
	for (int i=0;i<randcase;++i) //randomize all the points.
		swap(p[rand()%n],p[rand()%n]);
	center = p[0]; radius = 0; int useless;
	for (int i=1;i<n;++i) {
		if (dist(center,p[i])>radius+EPS) {
			center=p[i], radius = 0;
			for (int j=0;j<i;++j)
			if (dist(center,p[j])>radius+EPS) {
				center.x = (p[i].x+p[j].x)/2.0;
				center.y = (p[i].y+p[j].y)/2.0;
				radius = dist(center, p[j]);
				for (int k=0;k<j;++k)
				if (dist(center,p[k])>radius+EPS) {
				center = intersect(p[j].x-p[i].x,p[j].y-p[i].y,(p[j].x*p[j].x+
				p[j].y*p[j].y-p[i].x*p[i].x-p[i].y*p[i].y)/2,
				p[k].x-p[i].x,p[k].y-p[i].y,(p[k].x*p[k].x+
				p[k].y*p[k].y-p[i].x*p[i].x-p[i].y*p[i].y)/2,useless);
					radius = dist(center,p[k]);
    } } } }
}
void line2Points(double A, double B,double C, Point &p0, Point &p1) {
    if (sgn(A)==0) { p0 = Point(-C/A,0); p1 = Point(-(B+C)/A,1); }
    else { p0 = Point(0, -C/B); p1 = Point(1, -(A+C)/B); }
}
void points2Line(Point p0, Point p1, double &A, double &B, double &C) {
    A = p1.y-p0.y; B = p0.x-p1.x; C = p1.x*p0.y-p0.x*p1.y;
}
void plane2Points(double A, double B, double C, double D, Point3D &p0, Point3D &p1, Point3D &p2) {
    if(sgn(A)!=0){p0=Point3D(-D/A,0,0);p1=Point3D(-(B+D)/A,1,0);p2=Point3D(-(C+D)/A,0,1);} else
    if(sgn(B)!=0){p0=Point3D(0,-D/B,0);p1=Point3D(1,-(A+D)/B,0);p2=Point3D(0,-(C+D)/B,0);} else
    if(sgn(C)!=0){p0=Point3D(0,0,-D/C);p1=Point3D(1,0,-(A+D)/C);p2=Point3D(0,1,-(B+D)/C);}
}
template <typename T, int N> struct Matrix {
  T data[N][N];
  static Matrix<T,N> zero() { Matrix m = {}; return m; }
  static Matrix<T,N> identity() { Matrix m = {}; rep(i,N) m[i][i] = 1; return m; }
  Matrix<T,N> operator+(const Matrix<T,N>& other) const {
    Matrix res = {};
    rep(i,N) rep(j,N) res[i][j] = data[i][j] + other[i][j];
    return res;
  }
  Matrix<T,N> operator*(const Matrix<T,N>& other) const {
    Matrix res = {};
    rep(i,N) rep(k,N) rep(j,N) res[i][j] += data[i][k] * other[k][j];
    return res;
  }
  template <typename E> Matrix<T,N> operator^(E exp) const {
    Matrix<T,N> result = Matrix<T,N>::identity(), base = *this;
    while (exp) {
      if (exp & 1) result *= base;
      exp >>= 1;
      base *= base;
    }
    return result;
  }
  void multiply_vector(const T v[N], T result[N]) {
    rep(i, N) result[i] = 0;
    rep(i, N) rep(j, N) result[i] += data[i][j] * v[j];
  }
  const T* operator[](int i) const { return data[i]; }
  T* operator[](int i) { return data[i]; }
}; // creates a rotation matrix around axis x (must be normalized). Rotation is
// counter-clockwise if you look in the inverse direction of x onto the origin
template<typename M> void create_rot_matrix(M& m, double x[3], double a) {
  rep(i, 3) rep(j, 3) {
    m[i][j] = x[i]*x[j]*(1-cos(a));
    if (i == j) m[i][j] += cos(a);
    else m[i][j] += x[(6-i-j)%3] * ((i == (2+j) % 3) ? -1 : 1) * sin(a);
  }
}

