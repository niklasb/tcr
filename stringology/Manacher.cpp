/* Interleave s with '#' and prepend a '$': abcd => $#a#b#c#d#; len(news) = 2*n+2;
 * returns an array $P of length 2*n+2 in O(n) time where:
 * P[i] is the maxlen which can be extended from i (inclusive) to the left and right.
 * P[i]-1 is the max. length of palindrome centered at i.
 * start position of this palindrome in orig. string is i/2 - (P[i] + (i%2 == 0))/2 */
void Manacher(char *s, int n, int *P) {
	static char ts[mlen * 2 + 2];
	int N = 2 * n + 2;
	ts[0] = '$', ts[N - 1] = '#';
	for (int i = 0; i < n; ++i)	ts[i * 2 + 1] = '#', ts[i * 2 + 2] = s[i];
	int mx = 0, id = 0;
	memset(P, 0, sizeof(int) * N);
	for (int i = 1; i < N; i++) {
		P[i] = mx > i ? min(P[2 * id - i], mx - i) : 1;
		while (ts[i + P[i]] == ts[i - P[i]]) ++P[i];
		if (i + P[i] > mx) mx = i + P[i], id = i;
	}
}