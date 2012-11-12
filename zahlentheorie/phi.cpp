unsigned prime[NUM_PRIMES], phi[MAX];
bool used[NUM_PRIMES];
// Primzahlen muessen in prime stehen, Aufruf mit genphi(0, 1, 1)
void genphi(unsigned next, unsigned n, unsigned p) {
    phi[n] = p;
    while (next < primes && n <= MAX / prime[next]) {
        if (!used[next]) {
            used[next] = true;
            genphi(next, n * prime[next], p * (prime[next] - 1));
            used[next] = false;
        } else genphi(next, n * prime[next], p * prime[next]);
        ++next;
    }
}
