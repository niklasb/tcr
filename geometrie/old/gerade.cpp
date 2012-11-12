// Abstand des Punkts pos zum Ursprung
double norm(const vec& a) {return sqrt((a * a).sum());}

// Abstand zweier Punkte
double dist(const vec& a, const vec& b) {return norm(a - b);}

// Punkt auf Gerade durch Punkt pos in Richtung dir
// mit kleinstem Abstand zu Ursprung (orthogonale Projektion)
vec proj(const vec& pos, const vec& dir)
{return pos - (pos * dir).sum() / (dir * dir).sum() * dir;}

// Abstand Punkt-Gerade
double dist(const vec& pos, const vec& dir, const vec& pt)
{return norm(proj(pos - pt, dir));}

// Schnittpunkt Gerade durch pos in Richtung dir
// mit Gerade/Ebene durch Ursprung mit Normale norm
vec isect(const vec& pos, const vec& dir, const vec& norm)
{return pos - (pos * norm).sum() / (dir * norm).sum() * dir;}

// 2D-Schnittpunkt der Geraden durch Punkte a1-a2 und b1-b2
vec isect(const vec& a1, const vec& a2, const vec& b1, const vec& b2) {
    double temp[] = { a1[1] - a2[1], a2[0] - a1[0] };
    vec norm(temp, 2);
    return isect(b1 - a1, b2 - b1, norm) + a1;}

// Schnittpunkt Gerade durch pos in Richtung dir
// mit Kreis/Kugel um Ursprung mit Radius rad
inline vecvec isect(const vec& pos, const vec& dir, double rad) {
    double pp = (pos * pos).sum(), dd = (dir * dir).sum(),
           pd = (pos * dir).sum(), rr = rad * rad,
           dis = pd * pd - dd * (pp - rr);

    if (dis > EPS) {
        vecvec res(pos, 2);
        dis = sqrt(dis);
        res[0] -= (pd + dis) / dd * dir;
        res[1] -= (pd - dis) / dd * dir;
        return res;
    } else if (dis > -EPS) {
        vecvec res(pos, 1);
        res[0] -= pd / dd * dir;
        return res;
    }

    return vecvec();
}
