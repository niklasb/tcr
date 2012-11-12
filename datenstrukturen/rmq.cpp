#include <vector>
using std::vector;

// Wenn Range Maximum Query erwuenscht hier anpassen
inline int min(const int& a, const int& b) {return a < b ? a : b;}

class rmq
{
	int depth, inf;
	vector<int> data;
	
	inline int level(const int& i) {int r = 1; while (i > ((1<<r)-2)) r++; return depth-r+1;}
	inline int father(const int& i) {return (i-1)/2;}
	inline int lchild(const int& i) {return 2*i+1;}
	inline int rchild(const int& i) {return 2*i+2;}
	inline int lo(const int& i) {return (i-(1<<(depth-level(i)))+1)*(1<<level(i));}
	inline int hi(const int& i) {return (i-(1<<(depth-level(i)))+2)*(1<<level(i))-1;}
public:
	rmq(const int& size, const int& def)
	{// def ist der schlimmste Wert, +Inf bei Minimum, -Inf bei Maximum
		depth = 0; inf = def;
		int i = 1;
		while (i < size) {i <<= 1; depth++;}
		data = vector<int>(2*i-1, def);
	}
	void set(const int& index, const int& value) {
		int c = (1<<depth)-1+index;
		data[c] = value;
		while (c)
		{
			c = father(c);
			data[c] = min(data[lchild(c)], data[rchild(c)]);
		}
	}
	int get(const int& index) {
		return data[(1<<depth)-1+index];
	}
	int getmin(const int& from, const int& to, const int& node = 0) {
		if (from <= lo(node) && to >= hi(node)) return data[node];	// total hit
		else if (from > hi(node) || to < lo(node)) return inf;	// total miss
		else return min(getmin(from, to, lchild(node)), getmin(from, to, rchild(node)));
	}
};
