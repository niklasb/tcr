struct SA {
  const int maxn = 200010, maxlg = 18; // maxlg = ceil(log_2(maxn))
  pair<pii, int> L[maxn]; // O(n * log n) space
  int P[maxlg][maxn], n, stp, cnt, sa[maxn];
  string s;
  SA(string& s) : s(s), n(s.size()) {
    rep(i,0,n) P[0][i]=s[i];
    sa[0] = 0; // in case n == 1
    for (stp = 1, cnt = 1; cnt < n; stp++, cnt <<= 1) {
      rep(i,0,n)
        L[i] = mk(mk(P[stp-1][i], i + cnt < n ? P[stp-1][i+cnt] : -1), i);
      sort(L, L + n);
      rep(i,0,n)
        P[stp][L[i].snd] = i>0 && L[i].fst == L[i-1].fst ?  P[stp][L[i-1].snd] : i;
    }
    rep(i,0,n) sa[i] = L[i].snd;
  }
  int lcp(int x, int y) { // time log(n); x, y = indices into string, not SA
    int k, ret = 0;
    if (x == y) return n - x;
    for (k = stp - 1; k >= 0 && x < n && y < n; k --)
      if (P[k][x] == P[k][y])
        x += 1<<k, y += 1<<k, ret += 1<<k;
    return ret;
  }
  int find_succ(string& p) { // O(log n * |p|), find succ of p in suffix array
    int lo = 0, hi = n;
    while (lo < hi) {
      int m = (lo+hi)>>1;
      if (lexicographical_compare(s.begin() + sa[m], s.end(), all(p))) lo = m + 1;
      else hi = m;
    }
    return lo;
  }
}
