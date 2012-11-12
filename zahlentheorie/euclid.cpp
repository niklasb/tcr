#include <algorithm>
#include <valarray>
#include <vector>

using namespace std;

typedef valarray<int> ai;
typedef vector<int> vi;

// a % euclid(a, b)[0] == 0
// b % euclid(a, b)[0] == 0
// euclid(a, b)[0] == a * euclid(a, b)[1] + b * euclid(a, b)[2]
ai euclid(int a, int b) {
    int R[] = { a, 1, 0 }, S[] = { b, 0, 1 };
    ai r(R, 3), s(S, 3);

    while (s[0] != 0) {
        r -= r[0] / s[0] * s;
        swap(r, s);
    }
    
    return r;
}

// alle Loesungen von (a * x) % m == b mit 0 <= x < m
vi cong_solv(int a, int b, int m) {
    ai gcd = euclid(a, m);
    vi res;

    if (b % gcd[0] == 0) {
        m /= gcd[0];
        int inv = gcd[1] < 0 ? (m - (-gcd[1] % m)) % m : gcd[1] % m,
            sol = (b / gcd[0] * inv) % m;
        for (int i = gcd[0]; i > 0; --i) {
            res.push_back(sol);
            sol += m;
        }
    }

    return res;
}
