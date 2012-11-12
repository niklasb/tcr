// Laufzeit in O(b - a) garantiert, sonst wie std::nth_element
int select(int* a, int* b, int n) {
	if (b - a < 10000) { nth_element(a, a + n, b); return a[n]; }
	int* q = a;
	for (int *p = a; b - p >= 5; p += 5) { nth_element(p, p + 2, p + 5); swap(*q++, p[2]); }
	q = partition(a, b, bind2nd(less<int>(), select(a, q, (q - a) / 2)));
	return n < q - a ? select(a, q, n) : select(q, b, n - (q - a));
}
