#include <vector>
// Element veraendern UND kumulative Summe auslesen geht in O(log n)
class fenwick
{
	vector<int> a;	
public:
	fenwick(int n) : a(n) {}

	// v[i] += k
	void incr(int i, int k)	{a[i] += k;	while (i > 0) {i &= i - 1; a[i] += k;} }

	// Summe von a[0] bis a[i] (inkl.)
	int get(int i) {int r = a[0]; while (++i < int(a.size())) {r -= a[i]; i |= i - 1;}
		return r;}
};