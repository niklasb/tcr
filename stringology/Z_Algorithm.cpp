/* calculate the $z array for string $s of length $n in O(n) time.
 * z[i] := the longest common prefix of s[0..n-1] and s[i..n-1].
 * For pattern matching, make a string P$S and output positions with z[i]==|P|
 * For pattern matching, there's no need to store (but to calculate) z[i] for i>|P|. */
void calc_Z(const char *s, int n, int *z) {
	int l = 0, r = 0, p, q;
	if(n > 0) z[0] = n;
	for (int i = 1; i < n; ++i) {
		if (i <= r && z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			if (i > r) p = 0, q = i;
			else p = r - i + 1, q = r + 1;
			while (q < n && s[p] == s[q]) ++p, ++q;
			z[i] = q - i, l = i, r = q - 1;
		}
	}
}

