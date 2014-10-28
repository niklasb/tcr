typedef unsigned long long ULL;
typedef long long LL;
typedef map<ULL, short> factors;

LL MultiplyMod(LL a, LL b, LL mod) { //computes a * b % mod
    ULL r = 0;
    a %= mod, b %= mod;
    while (b) {
        if (b & 1) r = (r + a) % mod;
        b >>= 1, a = ((ULL) a << 1) % mod;
    }
    return r;
}
template<typename T>
T PowerMod(T a, T n, T mod) {  //computes a^n % mod
    T r = 1;
    while (n) {
        if (n & 1) r = MultiplyMod(r, a, mod);
        n >>= 1, a = MultiplyMod(a, a, mod);
    }
    return r;
}
template<typename T>
bool isprime(T n) { //determines if n is a prime number
    const int pn = 9, p[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23 };
    for (int i = 0; i < pn; ++i)
        if (n % p[i] == 0) return n == p[i];
    if (n < p[pn - 1]) return 0;
    T s = 0, t = n - 1;
    while (~t & 1)
        t >>= 1, ++s;
    for (int i = 0; i < pn; ++i) {
        T pt = PowerMod<T> (p[i], t, n);
        if (pt == 1) continue;
        bool ok = 0;
        for (int j = 0; j < s && !ok; ++j) {
            if (pt == n - 1) ok = 1;
            pt = MultiplyMod(pt, pt, n);
        }
        if (!ok) return 0;
    }
    return 1;
}
template<typename T>
T GCD(T a, T b) { 
    T r;
    while (b)
        r = a % b, a = b, b = r;
    return a;
}
template<typename T>
T _pollard_rho(T N) { 
    if (isprime<T> (N)) return N;
    int c = 2;
    do {
        T x = rand(), y = (x * x + c) % N, d = 1;
        int pow = 1, len = 1;
        while (1) {
            if (len++ == pow) x = y, pow <<= 1, len = 0;
            y = (MultiplyMod(y, y, N) + c) % N;
            if (x == y) break;
            d = GCD<T> ((x > y ? x - y : y - x), N);
            if (d != 1) return d;
        }
        do
            c = rand();
        while (c == 0);
    } while (1);
    return 0;
}

template<typename T>
void _factor_large(T N, factors &facts, short exp) {
    if (N == 1) return;
    T f = _pollard_rho<T> (N);
    if (f == N) {
        facts[f] += exp;
        return;
    }
    short c = 0;
    while (N % f == 0)
        N /= f, ++c;
    _factor_large(f, facts, exp * c);
    _factor_large(N, facts, exp);
}
int getprimes(int *pr, int maxp) {
    int mr = maxp * 20;
    bool *isp = new bool[mr];
    memset(isp, 1, mr);
    for (int i = 2; i * i < mr; ++i)
        if (isp[i]) {
            for (int j = i * i; j < mr; j += i)
                isp[j] = 0;
        }
    int c = 0;
    for (int i = 2; i < mr && c < maxp; ++i)
        if (isp[i]) pr[c++] = i;
    delete[] isp;
    return c;
}
template<typename T>
void factor(T N, factors &facts) {  //factors N into prime factors in facts
    const int mp = 100;
    static int pr[mp], pn = -1;
    if (pn == -1) pn = getprimes(pr, mp);
    for (int i = 0; i < pn; ++i)
        if (N % pr[i] == 0) {
            short c = 0;
            while (N % pr[i] == 0)
                N /= pr[i], ++c;
            facts[pr[i]] += c;
        }
    _factor_large<T> (N, facts, 1);
}
// calculate d = gcd(a, b), and x,y so that a x + b y = d
template<typename T>
T ex_gcd(T a, T b, T &x, T &y) {
    T q, r, x1 = 0, y1 = 1, x2, y2;
    x = 1, y = 0;
    while (b) {
        q = a / b, r = a % b;
        x2 = x - q * x1, y2 = y - q * y1;
        a = b, b = r, x = x1, x1 = x2, y = y1, y1 = y2;
    }
    return a;
}
// solve the linear congruence equation: a x == b (mod n)
//      the number of solutions up to congruence (can be 0).
//      sol: the minimal positive solution
//      dis: the distance between solutions
template<typename T>
T LinearMod(T a, T b, T n, T &sol, T &dis) {
    a = (a % n + n) % n, b = (b % n + n) % n;
    T d, x, y;
    d = ex_gcd<T> (a, n, x, y);
    if (b % d) return 0;
    x = (x % n + n) % n;
    x = MultiplyMod(b / d, x, n); //use normal mult instead if T = int
    dis = n / d;
    sol = x % dis;
    return d;
}

// find x.  a[i] x = b[i] (mod m[i])  0 <= i < n. m[i] need not be coprime
template<typename T>
bool ChineseRemainderTheorem(int n, T *a, T *b, T *m, T &sol, T &mod) {
    T A = 1, B = 0, ta, tm, tsol, tdis;
    for (int i = 0; i < n; ++i) {
        if (!LinearMod<T> (a[i], b[i], m[i], tsol, tdis)) return 0;
        ta = tsol, tm = tdis;
        if (!LinearMod<T> (A, ta - B, tm, tsol, tdis)) return 0;
        B = A * tsol + B;
        A = A * tdis;
    }
    sol = B, mod = A;
    return 1;
}
// compute p(n,k), the number of possibilities to write n as a sum of
// k non-zero integers
ll NrPartitions(int n, int k) {
    if (n==k) return 1;
    if (n<k || k==0) return 0;
    ll *p = new ll[n+1];
    for (int i = 1; i <= n; ++i) p[i] = 1;
    for (int l = 2; l <= k; ++l)
        for (int m = l+1; m <= n-l+1; ++m)
            p[m] = p[m] + p[m-l];
    delete[] p;
    return p[n-k+1];
}
// factors_p1 = prime factors of (p - 1)
bool is_primitive(ll g) {
  for (auto q : factors_p1) 
    if (1 == powmod(g, (p-1)/q)) return 0;
  return 1;
}
void find_prim() { // find primitive root of p
  ll g;
  for (;;) {
    g = (((ll)rand() << 15) | (ll)rand()) % p;
    if (g < 2) continue;
    if (is_primitive(g)) return;
  } return g;
}
ll dlog(ll b) { // find x such that g^x = b (mod p)
  ll m = (ll)(ceil(sqrt(p-1))+0.5); // better use binary search here...
  unordered_map<ll,ll> powers; // should compute this only once per g
  rep(j,0,m) powers[powmod(g, j)] = j;
  ll gm = powmod(g, -m + 2*(p-1));
  rep(i,0,m) {
    if (contains(powers, b)) return i*m + powers[b];
    b = b * gm % p;
  }
  assert(0); return -1;
}
