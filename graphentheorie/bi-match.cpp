#include <algorithm>
 
#define FROM_N 1000
#define TO_N 1000
 
int from_nodes, to_nodes;
 
bool graph[FROM_N][TO_N], seen[TO_N];
 
int match_from[FROM_N], match_to[TO_N];
 
bool match_visit(int from) {
	for (int to = 0; to < to_nodes; ++to) {
		if (graph[from][to] && !seen[to]) {
			seen[to] = true;
 
			if (match_to[to] < 0 || match_visit(match_to[to])) {
				match_from[from] = to;
				match_to[to] = from;
				return true;
			}
		}
	}
 
	return false;
}
 
int match() {
	int res = 0;
 
	fill(match_from, match_from + from_nodes, -1);
	fill(match_to, match_to + to_nodes, -1);
	for (int i = 0; i < from_nodes; ++i) {
		fill(seen, seen + to_nodes, false);
		if (match_visit(i)) {
			++res;
		}
	}
 
	return res;
}
