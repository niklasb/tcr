#include <cstdio> //hdu 3397, change [a,b] to 0/1, flip [a,b], popcnt([a,b]), longest continuous 1's
#include <algorithm>
using namespace std;
const int maxp = 200005, maxmark = 4, unmarked = 3;
const int trans[maxmark][maxmark] = { { 0, 1, 1, 0 }, { 0, 1, 0, 1 }, { 0, 1,unmarked, 2 }, { 0, 1, 2, unmarked } };
struct node {
    int mark, cnt, cont0, cont0l, cont0r, cont1, cont1l, cont1r; //cnt=number of 1's
    node *lc, *rc;
}*root, pool[maxp];
int pp;

struct triple { int a, b, c; triple(int x = 0, int y = 0, int z = 0) : a(x), b(y), c(z) {} };

void setfields(node *r, int m, int c, int c0, int c0l, int c0r, int c1,int c1l, int c1r) {
    r->mark = m;
    r->cnt = c;
    r->cont0 = c0, r->cont0l = c0l, r->cont0r = c0r;
    r->cont1 = c1, r->cont1l = c1l, r->cont1r = c1r;
}
inline void combine_mark(node *r, int m) { r->mark = trans[r->mark][m];}
inline void transmit(node *r, int lr, int rr) {
    if (r->lc) combine_mark(r->lc, r->mark);
    if (r->rc) combine_mark(r->rc, r->mark);
    int s = rr - lr + 1;
    switch (r->mark) {
        case 0: //set to 0
            setfields(r, unmarked, 0, s, s, s, 0, 0, 0); break;
        case 1: //set to 1
            setfields(r, unmarked, s, 0, 0, 0, s, s, s); break;
        case 2: //invert
            r->mark = unmarked;
            r->cnt = s - r->cnt;
            swap(r->cont0, r->cont1);
            swap(r->cont0l, r->cont1l);
            swap(r->cont0r, r->cont1r);
            break;
    }
}
void maintain(node *r, int lr, int rr) {
    const node &lc = *r->lc, &rc = *r->rc;
    int m = (lr + rr) >> 1;
    int l1 = m - lr + 1, l2 = rr - m;
    if (lc.mark != unmarked) transmit(r->lc, lr, m);
    if (rc.mark != unmarked) transmit(r->rc, m + 1, rr);

    r->cnt = lc.cnt + rc.cnt;
    r->cont0 = max(max(lc.cont0, rc.cont0), lc.cont0r + rc.cont0l);
    r->cont1 = max(max(lc.cont1, rc.cont1), lc.cont1r + rc.cont1l);
    r->cont0l = lc.cont0l + (lc.cont0l == l1 ? rc.cont0l : 0);
    r->cont1l = lc.cont1l + (lc.cont1l == l1 ? rc.cont1l : 0);
    r->cont0r = rc.cont0r + (rc.cont0r == l2 ? lc.cont0r : 0);
    r->cont1r = rc.cont1r + (rc.cont1r == l2 ? lc.cont1r : 0);
}
void segtree_build(node *&r, int lr, int rr) {
    r = pool + pp++;
    setfields(r, unmarked, 0, 0, 0, 0, 0, 0, 0);
    r->lc = r->rc = 0;
    if (lr == rr) {
        scanf("%d", &r->cnt);
        r->cont0 = r->cont0l = r->cont0r = !r->cnt;
        r->cont1 = r->cont1l = r->cont1r = r->cnt;
    } else {
        segtree_build(r->lc, lr, (lr + rr) >> 1);
        segtree_build(r->rc, ((lr + rr) >> 1) + 1, rr);
        maintain(r, lr, rr);
    }
}

void segtree_init(int n) { pp = 0;  root = 0;    segtree_build(root, 1, n); }

void segtree_modify(node *r, int lr, int rr, int il, int ir, int op) {
    if (r->mark != unmarked) transmit(r, lr, rr);
    if (il <= lr && rr <= ir) { r->mark = op;}
    else {
        int m = (lr + rr) >> 1;
        if (il <= m) segtree_modify(r->lc, lr, m, il, ir, op);
        if (m < ir) segtree_modify(r->rc, m + 1, rr, il, ir, op);
        maintain(r, lr, rr);
    }
}

triple segtree_query(node *r, int lr, int rr, int il, int ir, int op) {
    if (r->mark != unmarked) transmit(r, lr, rr);
    if (il <= lr && rr <= ir) {
        switch (op) {
            case 0: return triple(r->cnt); //count 1
            case 1: return triple(r->cont1, r->cont1l, r->cont1r); //longest continuous 1's
        }
    } else {
        int m = (lr + rr) >> 1;
        triple q1, q2;
        if (il <= m) q1 = segtree_query(r->lc, lr, m, il, ir, op);
        if (m < ir) q2 = segtree_query(r->rc, m + 1, rr, il, ir, op);
        switch (op) {
            case 0: return triple(q1.a + q2.a);
            case 1:
                triple q(max(max(q1.a, q2.a), q1.c + q2.b), q1.b, q2.c);
                if (il <= m && ir <= m) q.c = q1.c;
                else if (il > m && ir > m) q.b = q2.b;
                else if (il <= m && ir > m) {
                    int l1 = m - max(il, lr) + 1, l2 = min(ir, rr) - m;
                    if (q.b == l1) q.b += q2.b;
                    if (q.c == l2) q.c += q1.c;
                }
                return q;
        }
    }
    return triple();
}
int main() {
    int T, n, m, c, a, b;
    triple q;   scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        segtree_init(n);
        while (m--) {
            scanf("%d%d%d", &c, &a, &b);
            ++a, ++b;
            switch (c) {
                case 0: segtree_modify(root, 1, n, a, b, 0); break;//set to 0
                case 1: segtree_modify(root, 1, n, a, b, 1); break;//set to 1
                case 2: segtree_modify(root, 1, n, a, b, 2); break;//invert
                case 3: q = segtree_query(root, 1, n, a, b, 0); printf("%d\n", q.a); break; //count 1
                case 4: q = segtree_query(root, 1, n, a, b, 1); printf("%d\n", q.a); break;//longest 1's
            }
        }
    }
}
