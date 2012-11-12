#define INFTY 0x7FFFFFFF

struct edge {int to; int len;};

// Rueckgabe ist Array mit den Entfernungen oder leerer vector wenn der Graph einen negativen Kreis hat
vector<int> bellman_ford(const vector<vector<edge> >& graph, int source) {
	vector<int> dist(graph.size(), INFTY);
	dist[source] = 0;
	for (size_t j = 1; j < graph.size(); j++) {
		for (size_t from = 0; from < graph.size(); from++)
			for (size_t i = 0; i < graph[from].size()]; i++) {
				const int& to = graph[from][i].to;
				int cdist = dist[from] + graph[from][i].len;
				if (cdist < dist[to]) dist[to] = cdist;
			}
	}
	for (size_t from = 0; from < graph.size(); from++)
		for (size_t i = 0; i < graph[from].size(); i++) {
			const int& to = graph[from][i].to;
			int cdist = dist[from] + graph[from][i].len;
			if (cdist < dist[to]) return vector<int>();
		}
	return dist;
}