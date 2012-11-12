#include <algorithm>
#include <functional>
#include <vector>
class union_find
{
	vector<int> v;
public:
	union_find(int n) {v = vector<int>(n, -1);}
	
	int root(int i) {return v[i] < 0 ? i : (v[i] = root(v[i]));}
	
	void join(int i, int j)
	{
		if ((i = root(i)) == (j = root(j))) return;
		if (v[j] < v[i]) swap(i, j);
		v[i] += v[j];
		v[j] = i;
	}
	
	int count_roots() {	return count_if(v.begin(), v.end(), bind2(less<int>(), 0));}
	
	vector<int> get_roots()
	{
		vector<int> r;
		remove_copy_if(v.begin(), v.end(), back_inserter(r), bind2nd(greater_equal<int>(), 0));
		return r;
	}
};