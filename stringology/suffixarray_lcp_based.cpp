const int ml = 200010, mlog = 18, malpha = 256; //mlog := [log2(ml)]

unsigned char lg2[ml + 1];
ll lcp_rnd[malpha], lcp_h[mlog + 1][ml];
//Time: n log n; Space: n log n
void lcp_init(const char *s, int len) {
	lg2[0] = lg2[1] = 0;
	for (int i = 2; i <= len; ++i) lg2[i] = lg2[i >> 1] + 1;
	for (int i = 0; i < malpha; ++i)
		lcp_rnd[i] = ((ll) rand() << 45) + ((ll) rand() << 30)+ ((ll) rand() << 15) + rand();
	// linux: lcp_rnd[i] = ((LL)rand()<<31) + rand()
	for (int i = len - 1; i >= 0; --i) {
		lcp_h[0][i] = lcp_rnd[(int) s[i]];
		for (int j = 1; j <= lg2[len - i]; ++j)
			lcp_h[j][i] = lcp_h[j - 1][i] * lcp_rnd[j] ^ lcp_h[j - 1][i + (1 << (j - 1))];
	}
}
//i and j are suffix indices, not indices into the suffix array! Time:log n
int lcp_query(const char *s, int len, int i, int j) {
	int r = i;
	for (int k = lg2[len], t = 1 << lg2[len]; k >= 0; t >>= 1, --k)
		if (i + t <= len && j + t <= len && lcp_h[k][i] == lcp_h[k][j])
			i += t, j += t;
	return i - r;
}
// Time = n log^2 n
void sa_build(const char *s, int len, int *sa) {
	lcp_init(s, len);
	for (int i = 0; i < len; ++i) sa[i] = i;
	sort(sa, sa + len, [&](int a, int b) {
        int l = lcp_query(s, len, a, b);
        return s[a+l] < s[b+l];
      });
}
