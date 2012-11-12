typedef long long LL;
const int ml = 100010, mlog = 17, malpha = 256; //mlog := [log2(ml)]

unsigned char log2[ml + 1];
LL lcp_rnd[malpha], lcp_h[mlog + 1][ml];
//Time: nlogn; Space: nlogn
void lcp_init(const char *s, int len) {
	log2[0] = log2[1] = 0;
	for (int i = 2; i <= len; ++i) log2[i] = log2[i >> 1] + 1;
	for (int i = 0; i < malpha; ++i)
		lcp_rnd[i] = ((LL) rand() << 45) + ((LL) rand() << 30)+ ((LL) rand() << 15) + rand();
	// linux: lcp_rnd[i] = ((LL)rand()<<31) + rand()
	for (int i = len - 1; i >= 0; --i) {
		lcp_h[0][i] = lcp_rnd[(int) s[i]];
		for (int j = 1; j <= log2[len - i]; ++j)
			lcp_h[j][i] = lcp_h[j - 1][i] * lcp_rnd[j] ^ lcp_h[j - 1][i + (1 << (j - 1))];
	}
}
//Time:logn
int lcp_query(const char *s, int len, int i, int j) {
	int r = i;
	for (int k = log2[len], t = 1 << log2[len]; k >= 0; t >>= 1, --k)
		if (i + t <= len && j + t <= len && lcp_h[k][i] == lcp_h[k][j])
			i += t, j += t;
	return i - r;
}
struct sa_cmp_class {
	const char *s;
	int len;
	bool operator()(int a, int b) const {
		int l = lcp_query(s, len, a, b);
		return s[a + l] < s[b + l];
	}
} sa_cmp;
// Time = n log^2 n
void sa_build(const char *s, int len, int *sa) {
	lcp_init(s, len);
	sa_cmp.s = s, sa_cmp.len = len;
	for (int i = 0; i < len; ++i) sa[i] = i;
	sort(sa, sa + len, sa_cmp);
}