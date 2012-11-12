int fast_exp(int a, int b) {
    int r = 1;

    while (b > 0) {
        if ((b & 1)) r *= a;
        b >>= 1;
        a *= a;
    }

    return r;
}
