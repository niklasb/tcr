// ruft do_something(x, y) mit allen (x, y) auf,
// die eine gerasterte Linie von (x0, y0) nach (x1, y1) bilden
void line(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0, dy = y1 - y0;
    int incrE = 2 * dy, incrNE = 2 * (dy - dx);
    int d = 2 * dy - dx, x = x0, y = y0;
    do_something(x, y);
    while (x < x1) {
        if (d > 0) { d += incrNE; ++y; } else d += incrE;
        do_something(++x, y);
    }
}
// ruft do_something(x, y) mit allen (x, y) auf,
// die einen gerasterten Achtelkreis um den Ursprung bilden
void circle(int radius) {
    int deltaE = 3, deltaSE = -2 * radius + 5;
    int d = 1 - radius, x = 0, y = radius;
    do_something(x, y);
    while (x < y) {
        if (d < 0) d += deltaE; else { d += deltaSE; deltaSE += 2; --y; }
        deltaE += 2; deltaSE += 2;
        do_something(++x, y);
    }
}
