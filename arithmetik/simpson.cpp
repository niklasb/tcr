double f(double x) { return exp(-x*x); }
const double eps=1e-12;

double simps(double a, double b) { // for ~4x less f() calls, pass fa,fm,fb around
  return (f(a) + 4*f((a+b)/2) + f(b))*(b-a)/6;
}
double integrate(double a, double b) {
  double m = (a+b)/2;
  double l = simps(a,m),r = simps(m,b),tot=simps(a,b);
  if (fabs(l+r-tot) < eps) return tot;
  return integrate(a,m) + integrate(m,b);
}
