// Schnittpunkte von Kreis um 0 mit Radius r1 mit Kreis um Punkt pos mit Radius r2
vecvec isect(double r1, vec pos, double r2) {
    double d2 = (pos * pos).sum(), d = sqrt(d2);
    r1 *= r1; r2 *= r2;
    double x = 0.5 * (d2 + r1 - r2) / d, y2 = r1 - x * x;

    if (y2 > EPS) {
        double norma[] = { -pos[1], pos[0] };
        vec norm(norma, 2);
        vecvec r(x / d * pos, 2);
        y2 = sqrt(y2);
        r[0] += y2 / d * norm;
        r[1] -= y2 / d * norm;
        return r;
    } else if (y2 > -EPS) {
        return vecvec(x / d * pos, 1);
    }
    return vecvec();
}
