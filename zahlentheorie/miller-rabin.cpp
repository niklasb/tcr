typedef unsigned long long ull;
const struct zero_t {
    int z[0x10000];
    zero_t() {
        for (int i = 1; i < 0x10000; ++i) z[i] = (i & 1) ? 0 : 1 + z[i >> 1];
    }
} trail;
inline bool isprob(unsigned nr, unsigned base) {
    unsigned u = 1, odd = nr - 1, sh = (odd & 0xFFFF)
        ? trail.z[odd & 0xFFFF] : 16 + trail.z[odd >> 16];
    for (odd >>= sh; odd > 0; odd >>= 1) {
        if ((odd & 1)) u = (ull(u) * base) % nr;
        base = (ull(base) * base) % nr;
    }
    if (u == 1) return true;
    while (sh-- > 0) {
        if (u == nr - 1) return true;
        u = (ull(u) * u) % nr;
    }
    return false;
}
bool isprime(unsigned nr) {
    static const unsigned p[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
    for (int i = 0; i < 8; ++i) {
        if (p[i] * p[i] > nr) return nr > 1;
        if (nr % p[i] == 0) return false;
    }
    return isprob(nr, 2) && isprob(nr, 7) && isprob(nr, 61);
}
