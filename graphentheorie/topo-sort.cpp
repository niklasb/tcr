// Gibt Knotenindizes in topologischer Reihenfolge, retval.size() < graph.size() falls Zyklen vorkommen
vector<int> topsort(const vector<vector<int> >& graph)
{
	vector<int> preds(graph.size(), 0);
	for (size_t i = 0; i < graph.size(); i++)
		for (size_t j = 0; j < graph[i].size(); j++)
			preds[graph[i][j]]++;
			
	std::queue<int> q;
	for (size_t i = 0; i < preds.size(); i++)
		if (!preds[i]) q.push(i);
		
	vector<int> sorted;
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		sorted.push_back(curr);
		for (size_t i = 0; i < graph[curr].size(); i++)
			if (!(--preds[graph[curr][i]]))
				q.push(graph[curr][i]);
	}
	return sorted;
}