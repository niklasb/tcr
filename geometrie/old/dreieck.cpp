// Flaeche des durch a und b aufgespannten Parallelogramms
// positiv, wenn Winkel zwischen a und b positiv
double sgn_area(const vec& a, const vec& b) {return a[0] * b[1] - a[1] * b[0];}

// positiv, wenn a-b-c im Gegenuhrzeigersinn (math. positiv) liegen
double sgn_area(const vec& a, const vec& b, const vec& c) {return sgn_area(b - a, c - a);}

// Dreiecksflaeche
double area(const vec& a, const vec& b, const vec& c) {return 0.5 * fabs(sgn_area(a, b, c));}

// Dreiecksflaeche aus Seitenlaengen
double area(double a, double b, double c) {
    if (a < b) swap(a, b); if (b < c) swap(b, c); if (a < b) swap(a, b);
    return 0.25 * sqrt((a + (b + c)) * (c - (a - b)) * (c + (a - b)) * (a + (b - c)));}

// true, wenn a und b verschiedene Vorzeichen haben
inline bool pos_neg(double a, double b) {return (a < 0 && 0 < b) || (b < 0 && 0 < a);}

// true, wenn Punkt d in Dreieck mit Eckpunkten a-b-c liegt
bool inside(const vec& a, const vec& b, const vec& c, const vec& d) {
    double x = sgn_area(c, b, a);
    return pos_neg(x, sgn_area(a, b, d))
        && pos_neg(x, sgn_area(b, c, d))
        && pos_neg(x, sgn_area(c, a, d));}

// true, wenn Punkt c in achsenparallelem Rechteck durch Punkt a und b liegt
bool inside(const vec& a, const vec& b, const vec& c) {
    return min(a[0], b[0]) < c[0] + EPS && max(a[0], b[0]) > c[0] - EPS
        && min(a[1], b[1]) < c[1] + EPS && max(a[1], b[1]) > c[1] - EPS;}

// true, wenn c auf Segment a-b liegt bzw. gleich a oder b ist
bool on_seg(const vec& a, const vec& b, const vec& c) {
    return inside(a, b, c) && fabs(sgn_area(a, b, c)) < EPS;}

// Schnitt der Liniensegmente a1-a2 und b1-b2
// 0 = kein Schnitt, 1 = Schnitt, -1 = Beruehrung
int isect(const vec& a1, const vec& a2, const vec& b1, const vec& b2) {
    double da1 = sgn_area(b1, b2, a1), da2 = sgn_area(b1, b2, a2),
           db1 = sgn_area(a1, a2, b1), db2 = sgn_area(a1, a2, b2);

    if (pos_neg(da1, da2) && pos_neg(db1, db2)) return 1;
    if (on_seg(a1, a2, b1) || on_seg(a1, a2, b2)
     || on_seg(b1, b2, a1) || on_seg(b1, b2, a2)) return -1;
    return 0;}
